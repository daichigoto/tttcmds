/*
 * Copyright (c) 2016,2017 Daichi GOTO
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
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "@:shvD",
	           CMDARGS_R_NEED|
		   CMDARGS_R_ARGARG_1_NEED|
		   CMDARGS_R_ARGARG_TO_SSVSTR); 

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
			mode[R_ARGV[i]] = DO_ASSIGN;
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
