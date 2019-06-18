/*
 * Copyright (c) 2016,2017,2019 Daichi GOTO
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

int 
has_option_m_with_simple(int argc, char *argv[])
{
	int i;
	for (i = 1; i < argc; i++) {
		if (0 == strcmp("-m", argv[i])) {
			if (i + 1 < argc) {
				if (0 == strcmp("simple", argv[i+1])) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int
main(int argc, char *argv[])
{
	if (has_option_m_with_simple(argc, argv)) {
		getcmdargs(argc, argv, "@:f:m:shvD",
		           CMDARGS_R_NEED|
			   CMDARGS_R_ARGARG_1_NEED|
			   CMDARGS_R_ARGARG_TO_SSVSTR|
			   CMDARGS_DELIMITER_ONLY_1); 
	}
	else {
		getcmdargs(argc, argv, "@:f:m:shvD",
		           CMDARGS_R_NEED|
			   CMDARGS_R_ARGARG_1_NEED|
			   CMDARGS_R_ARGARG_TO_SSVSTR);
	}

	char *at = "@";
	if (FLAG_AT)
		at = _str2ssvstr(FLAG_AT_ARG);

	/*
	 * process mode assortment
	 */
	int mode[R_INDEX_MAX + 1];
	for (int i = 0; i <= R_INDEX_MAX; i++)
		mode[i] = DO_NOTHING;
	struct tttcmdargs r_cmdargs[R_INDEX_MAX + 1];

	char *matchswap[R_INDEX_MAX + 1];
	char *notmatchswap[R_INDEX_MAX + 1];

	char *filename;
	for (int i = 1; i <= R_ARGC; i++) {
		if (NULL == R_ARGV_ARG2[i] && NULL == R_ARGV_ARG3[i]) {
			if (FLAG_f)
				mode[R_ARGV[i]] = DO_ASSIGN_WITH_F;
			else
				mode[R_ARGV[i]] = DO_ASSIGN_WITHOUT_F;
		}
		else if (NULL != R_ARGV_ARG2[i] && NULL == R_ARGV_ARG3[i]) {
			if ('!' != R_ARGV_DELIM[i]) {
				mode[R_ARGV[i]] |= DO_MATCH_SWAP;
				matchswap[R_ARGV[i]] = R_ARGV_ARG2[i];
			}
			else {
				mode[R_ARGV[i]] |= DO_NOTMATCH_SWAP;
				notmatchswap[R_ARGV[i]] = R_ARGV_ARG2[i];
			}
		}
		else if (NULL != R_ARGV_ARG2[i] && NULL != R_ARGV_ARG3[i]) {
			mode[R_ARGV[i]] = DO_JOIN;

			filename = calloc(1, sizeof(char) *
				(strlen(cmdargs.r_argv_arg1[i]) + 1));
			strcpy(filename, cmdargs.r_argv_arg1[i]);	
			ssvstr2str(cmdargs.r_argv_arg1[i], filename);

			setcmdargs_from_FILENAME_RETU_RETU(
				&r_cmdargs[R_ARGV[i]], 
				cmdargs.r_argv_arg1[i],
				cmdargs.r_argv_arg2[i],
				cmdargs.r_argv_arg3[i],
				cmdargs.r_argv_delim[i]);
		}
	}

	/*
	 * process mode overwrite by -m option
	 */
	if (FLAG_m) {
		if (0 == strncmp("simple", FLAG_m_ARG, 6)) {
			for (int i = 1; i <= R_ARGC; i++) {
				if (FLAG_f)
					mode[R_ARGV[i]] = DO_ASSIGN_WITH_F;
				else
					mode[R_ARGV[i]] = DO_ASSIGN_WITHOUT_F;
			}
		}
		else if (0 == strncmp("condition", FLAG_m_ARG, 9)) {
			for (int i = 1; i <= R_ARGC; i++) {
				if ('!' != R_ARGV_DELIM[i]) {
					mode[R_ARGV[i]] |= DO_MATCH_SWAP;
					matchswap[R_ARGV[i]] = R_ARGV_ARG2[i];
				}
				else {
					mode[R_ARGV[i]] |= DO_NOTMATCH_SWAP;
					notmatchswap[R_ARGV[i]] = R_ARGV_ARG2[i];
				}
			}
		}
		else if (0 == strncmp("join", FLAG_m_ARG, 4)) {
			for (int i = 1; i <= R_ARGC; i++) {
				mode[R_ARGV[i]] = DO_JOIN;
	
				filename = calloc(1, sizeof(char) *
					(strlen(cmdargs.r_argv_arg1[i]) + 1));
				strcpy(filename, cmdargs.r_argv_arg1[i]);	
				ssvstr2str(cmdargs.r_argv_arg1[i], filename);
	
				setcmdargs_from_FILENAME_RETU_RETU(
					&r_cmdargs[R_ARGV[i]], 
					cmdargs.r_argv_arg1[i],
					cmdargs.r_argv_arg2[i],
					cmdargs.r_argv_arg3[i],
					cmdargs.r_argv_delim[i]);
			}
		}
		else {
			errx(EINVAL, "No such mode: %s", FLAG_m_ARG);
		}
	}

	/*
	 * array setup for simple assing (with -f) process
	 */
	char **a_array;
	int *i_to_ai, a_nf = 0;
	if (FLAG_f) {
		/*
		 * R_ARGV_ARG1[] to i_to_ai[]
		 */
		i_to_ai = (int *)calloc(R_ARGC+1, sizeof(int));
		for (int i = 1; i <= R_ARGC; i++) {
			errno = 0;
			i_to_ai[i] = (int)strtol(R_ARGV_ARG1[i], 
				(char **)NULL, 10);
			if (EINVAL == errno)
				usage();
		}

		/*
		 * file to a_array[][]
		 */
		FILE *fp = fopen(FLAG_f_ARG, "r");	
		if (NULL == fp)
			usage();
		char a_buf[1024*64], *a_buf_p;
		fgets(a_buf, 1024*64, fp);
		fclose(fp);

		a_buf_p = a_buf;
		while (*a_buf_p != '\0') {
			if (' ' == *a_buf_p)
				++a_nf;
			++a_buf_p;
		}
		if (a_buf[0] != '\n' && a_buf[0] != '\0')
			++a_nf;
		int len;
		a_buf_p = a_buf;
		a_array = (char **)calloc(a_nf+1, sizeof(char *));
		for (int i = 1; i <= a_nf; i++) {
			len = 0;
			while (*a_buf_p != ' ' && 
				*a_buf_p != '\n' && *a_buf_p != '\0') {
				++a_buf_p;
				++len;
			}
			a_array[i] = (char *)calloc(len+1, sizeof(char));
			memcpy(a_array[i], a_buf_p-len, len);

			if (*a_buf_p == '\n' || *a_buf_p == '\0')
				break;

			++a_buf_p;
		}
	}

	/*
	 * hashtable setup for join process
	 */
	DB *hashtables[R_INDEX_MAX + 1];
	DBT hash_key, hash_val;
	memset(hashtables, 0, (R_INDEX_MAX + 1) * sizeof(DB *));

	struct tttcmdargs cmdargs_org;
	cmdargs_org = cmdargs;

	int r_argc;
	for (int i = 1; i <= cmdargs_org.r_index_max; i++) {
		if (!(mode[i]&DO_JOIN))
			continue; 

		cmdargs = r_cmdargs[i];

		r_argc = cmdargs.r_argc;
		hashtables[i] = dbopen(NULL, O_CREAT|O_RDWR, 0644, 
			DB_HASH, NULL);
		if (NULL == hashtables[i])
			err(errno, "retu_assign: dbopen failed"); 

		hash_key.data = "\0";
		hash_key.size = 1;
		hash_val.data = getatmarkline(r_argc - 1, at);
		hash_val.size = strlen(hash_val.data);

		hashtables[i]->put(hashtables[i], &hash_key, &hash_val, 0);

		char *value, *v_p;
		int buf_len, value_len;
		FILEPROCESS_GYO
	}

	/*
	 * restore command cmdargs
	 */
	cmdargs = cmdargs_org;

	FILEPROCESS_RETU

	exit(EX_OK);
}
