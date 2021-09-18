/*
 * Copyright (c) 2016,2021 Daichi GOTO
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are 
 * met: 
 * 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "command.h"

/*---------------------------------------------------------------------
 * MSYS2
 *-------------------------------------------------------------------- */
#if defined(__MSYS__)

#include <windows.h>
#include <shlwapi.h>
#include <limits.h>
#include <fts.h>

static HANDLE openFile(char *);
static void printDirectoryTree(char *);
static void MSYS2PathToWindowsPath(char *);

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "phvD", CMDARGS_R_NONE|CMDARGS_F_NEED);

	// The type of path specified in the arguments.
	enum path_type {
		DIRECTORY,
		FILE
	};

	// The FindFirstChangeNotification() function used for notification 
	// uses the directory as the monitoring target. Therefore, if a file 
	// is specified as the monitoring target, the command will monitor 
	// the directory where the file resides, and if a change is detected,
	// the command will work by checking if the monitored file has been 
	// modified or not.
	// struct target is a structure to realize the above operation, which 
	// holds the handler for FindFirstChangeNotification() as well as 
	// data such as the path and the last modified time of the file.
	struct target {
		enum path_type	type;
		HANDLE		handle;
		char		dir_path[MAX_PATH];
		char		file_path[MAX_PATH];
		FILETIME	file_modtime;
	};
	int numer_of_targets = F_ARGC;
	struct target targets[numer_of_targets];

	// When monitoring multiple handlers with WaitForMultipleObjects(), 
	// an array of handlers is required. The following array is prepared 
	// for this purpose.
	HANDLE handles[numer_of_targets];

	// Parse the arguments and set up struct target targets[]
	for (int i = 0; i < numer_of_targets; i++) {
		char path_buf[MAX_PATH];
		strncpy(path_buf, F_ARGV[i+1], MAX_PATH);

		// Convert MSYS2 path to Windows path
		MSYS2PathToWindowsPath(path_buf);

		// A directory is specified
		if (PathIsDirectory(path_buf)) {
			targets[i].type = DIRECTORY;
			memcpy(targets[i].dir_path, path_buf, MAX_PATH);
			targets[i].file_path[0] = '\0';
		
			if (! PathFileExists(targets[i].dir_path)) {
				fprintf(stderr, 
			                "no such directory: %s\n", 
				         targets[i].dir_path);
				exit(EX_USAGE);
			}

			if (FLAG_p) {
				printDirectoryTree(targets[i].dir_path);
			}
		}
		// A file is specified
		else {
			targets[i].type = FILE;
			memcpy(targets[i].file_path, path_buf, MAX_PATH);

			if (! PathFileExists(targets[i].file_path)) {
				fprintf(stderr,
				        "no such file: %s\n", targets[i].file_path);
				exit(EX_USAGE);
			}

			// Get the last modified time of the file
			HANDLE hFile = openFile(targets[i].file_path);
			GetFileTime(hFile, NULL, NULL, &(targets[i].file_modtime));
			CloseHandle(hFile);

			// Set the directory to which the file belongs
			memcpy(targets[i].dir_path, path_buf, MAX_PATH);
			PathRemoveFileSpec(targets[i].dir_path);
			if ('\0' == targets[i].dir_path[0]) {
				targets[i].dir_path[0] = '.';
				targets[i].dir_path[1] = '\\';
				targets[i].dir_path[2] = '\0';
			}

			if (FLAG_p) {
				printf("%s\n",targets[i].file_path);
			}
		}

		if (FLAG_D) {
			if (DIRECTORY == targets[i].type) {
				fprintf(stderr, 
				        "TARGET PATH TYPE: DIRECTORY\n");
			}
			else {
				fprintf(stderr,
				        "TARGET PATH TYPE: FILE\n");
			}
			fprintf(stderr, 
			        "CANONICAL DIR PATH: %s\n",
				 targets[i].dir_path);
			fprintf(stderr,
			        "CANONICAL FILE PATH: %s\n", 
			         targets[i].file_path);
			if (FILE == targets[i].type) {
				fprintf(stderr,
				        "FILE LAST MOD TIME: %d %d\n", 
					targets[i].file_modtime.dwLowDateTime,
					targets[i].file_modtime.dwHighDateTime);
			}
			fprintf(stderr,"\n");
		}

		// Create a handler to monitor the directory
		targets[i].handle = FindFirstChangeNotification( 
			// directory path to be monitored
			targets[i].dir_path,
			// If the argument is a directory, subdirectories are 
			// also set as monitoring targets.
			DIRECTORY == targets[i].type ? TRUE : FALSE,
			// monitor writing to files
			FILE_NOTIFY_CHANGE_LAST_WRITE
		);
		
		if (INVALID_HANDLE_VALUE == targets[i].handle) {
			fprintf(stderr, 
			        "FindFirstChangeNotification: "
				"INVALID_HANDLE_VALUE: %s\n", F_ARGV[i+1]);
			exit(EX_USAGE);
		}

		// Preparing an array for use with WaitForMultipleObjects().
		handles[i] = targets[i].handle;
	}

	// Wait for iteration until the monitoring target is modified.
	while (true) {
		if (FLAG_D) {
			fprintf(stderr, "MONITERING STARTED\n");
		}

		// Wait until a write occurs to the monitoring targets.
		DWORD status = WaitForMultipleObjects(
			numer_of_targets,	// Number of handlers
			handles,		// Array of handlers
			FALSE,			// Exit when a handler responds
			1000			// timeout 1000[ms], for Ctrl-C
			/* INFINITE		// no timeout period */
		);

		if (WAIT_FAILED == status) {
			fprintf(stderr, "WAIT_FAILED\n");
			exit(EX_OSERR);
		}
		if (WAIT_TIMEOUT == status) {
			// In this implementation, Ctrl-C to exit the program 
			// does not work properly. I think the correct process
			// is to use _kbhit() to check the key input during 
			// wait and respond to Ctrl-C. However, I can't use 
			// _kbhit() in MSYS2 (at least I don't know how to 
			// solve it now). To my future self, please solve this 
			// problem.
			continue;
		}

		if (FLAG_D) {
			fprintf(stderr, 
			        "WaitForMultipleObjects: %d\n", status);
		}

		// If the monitoring target is a directory, terminate the 
		// monitoring process immediately.
		if (DIRECTORY == targets[status].type) {
			break;
		}
		// If the monitoring target is a file, check if the last 
		// time of the file has been updated, and if so, immediately 
		// terminate the monitoring process.
		else {
			FILETIME file_modtime;
			HANDLE hFile = openFile(targets[status].file_path);
			GetFileTime(hFile, NULL, NULL, &file_modtime);
			CloseHandle(hFile);

			if (FLAG_D) {
				fprintf(stderr, 
			                "BEFORE: %s: %d %d\n",
					 targets[status].file_path,
					 targets[status].file_modtime.dwLowDateTime,
					 targets[status].file_modtime.dwHighDateTime);
				fprintf(stderr, 
			                "AFTER: %s: %d %d\n",
					 targets[status].file_path,
					 file_modtime.dwLowDateTime,
					 file_modtime.dwHighDateTime);
			}

			if (targets[status].file_modtime.dwLowDateTime != 
				file_modtime.dwLowDateTime || 
			    targets[status].file_modtime.dwHighDateTime != 
				file_modtime.dwHighDateTime) {
				break;
			}
		}

		if (FALSE == FindNextChangeNotification(handles[status])) {
			fprintf(stderr, "FindNextChangeNotification FAILED\n");
			exit(EX_OSERR);
		}
	}

	exit(EX_OK);
}

static void
MSYS2PathToWindowsPath(char *path)
{
	int len = strlen(path);
	if (3 <= len) {
		if ('/' == path[0] &&
		    'c' == path[1] &&
		    '/' == path[2]) {
			path[0] = 'C';
			path[1] = ':';
			path[2] = '\\';
		}
	}
	for (int i = 0; i < len; i++) {
		if ('/' == path[i]) {
			path[i] = '\\';
		}
	}
}

static HANDLE
openFile(char *file_path)
{
	HANDLE hFile = CreateFile(
		TEXT(file_path),	// file to open
		GENERIC_READ,		// open for reading
		FILE_SHARE_READ,	// share for reading
		NULL,			// default security
		OPEN_EXISTING,		// open existing file
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL			// no template file
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		fprintf(stderr,
		        "can't open file: %s\n", file_path);
		exit(EX_IOERR);
	}
	return hFile;
}

static void
printDirectoryTree(char *dir_path)
{
	FTS *tree;
	FTSENT *ent;

	tree = fts_open(&dir_path, FTS_LOGICAL, NULL);
	while (NULL != (ent = fts_read(tree))) {
		printf("%s\n", ent->fts_path);
	}
	fts_close(tree);
}

/*---------------------------------------------------------------------
 * Linux
 *-------------------------------------------------------------------- */
#elif defined(__linux__)
int
main(int argc, char *argv[])
{
	//XXX
	// Not implemented yet for Linux.
	// You must implement using inotify or epoll(7)? I don't know well.
	argc = 0;
	argv[0] = NULL;
	exit(EX_UNAVAILABLE);
}

/*---------------------------------------------------------------------
 * FreeBSD / Mac
 *-------------------------------------------------------------------- */
#else
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fts.h>

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "phvD", CMDARGS_R_NONE|CMDARGS_F_NEED);

	struct stat sb;
	struct kevent ke;
	int kq, i, set;
	char *tgts[F_ARGC];
	FTS *tree;
	FTSENT *ent;

	for (i = 0; i < F_ARGC; i++)
		tgts[i] = F_ARGV[i+1];
	tgts[F_ARGC] = NULL;

	set = 0;
	kq = kqueue();
	tree = fts_open(tgts, FTS_LOGICAL, NULL);
	while (NULL != (ent = fts_read(tree))) {
		if (-1 == stat(ent->fts_path, &sb)) {
			warnc(errno, "%s", ent->fts_path);
			continue;
		}
		FILEPROCESS_OPEN(i, ent->fts_path, O_RDONLY)
		EV_SET(&ke, i, EVFILT_VNODE, EV_ADD|EV_CLEAR,
		       NOTE_DELETE|NOTE_WRITE|NOTE_EXTEND|
		       NOTE_ATTRIB|NOTE_RENAME, 0, NULL);
		kevent(kq, &ke, 1, NULL, 0, NULL);
		set = 1;

		if (FLAG_p)
			printf("%s\n", ent->fts_path);
	}
	fts_close(tree);

	if (set)
		kevent(kq, NULL, 0, NULL, 1, NULL);

	exit(EX_OK);
}
#endif
