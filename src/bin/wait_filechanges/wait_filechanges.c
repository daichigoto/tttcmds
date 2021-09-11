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

// DEGRADATION
//
// This command can specify files as the monitoring targets, but the Windows 
// FindFirstChangeNotification() function cannot specify a file as the 
// monitoring target. For this reason, we assume that only directories can 
// be specified for monitoring on Windows.
//
// Also, we don't support option -p on Windows (Although this can be 
// implemented... eventually, when I get around to it, maybe).
int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "hvD", CMDARGS_R_NONE|CMDARGS_F_NEED);

	HANDLE **handle;
	handle = calloc(F_ARGC, sizeof(HANDLE *));

	for (int i = 0; i < F_ARGC; i++) {
		handle[i] = FindFirstChangeNotification( 
			F_ARGV[i+1], 	// directory path to be monitored
			TRUE,		// subdirectories are also coverd
			FILE_NOTIFY_CHANGE_LAST_WRITE
					// detects writing to files
		);
		if (INVALID_HANDLE_VALUE == handle[i]) {
			fprintf(stderr, 
			        "FindFirstChangeNotification: "
				"INVALID_HANDLE_VALUE: %s\n", F_ARGV[i+1]);
			exit(EX_USAGE);
		}
	}

	exit(EX_OK);
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
		i = open(ent->fts_path, O_RDONLY);
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
