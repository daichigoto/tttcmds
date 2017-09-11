/*
 * Copyright (c) 2017 Daichi GOTO
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
	getcmdargs(argc, argv, "rhvD", CMDARGS_R_NEED);

	/*
	 * column specifics setup
	 */
	DB *hashtables[R_INDEX_MAX + 1];
	DBT hash_key, hash_val;
	memset(hashtables, 0, (R_INDEX_MAX + 1) * sizeof(DB *));
	for (int i = 1; i <= R_ARGC; i++) {
		if (NULL == hashtables[R_ARGV[i]])
			hashtables[R_ARGV[i]] = 
				dbopen(NULL, O_CREAT|O_RDWR, 0644, 
					DB_HASH, NULL);

		if (NULL == cmdargs.r_argv_arg1[i] &&
		    NULL == cmdargs.r_argv_arg2[i] &&
		    NULL == cmdargs.r_argv_arg3[i])
			continue;

		if (NULL == cmdargs.r_argv_arg1[i] &&
		    NULL == cmdargs.r_argv_arg2[i] &&
		    NULL == cmdargs.r_argv_arg3[i])
			usage();

		if (0 == strncmp(cmdargs.r_argv_arg1[i], "_attr_", 6)) {
			hash_key.data = cmdargs.r_argv_arg2[i];
			hash_key.size = strlen(hash_key.data) + 1;
			hash_val.data = _str2ssvstr(cmdargs.r_argv_arg3[i]);
			hash_val.size = strlen(hash_val.data) + 1;

			hashtables[R_ARGV[i]]->put(hashtables[R_ARGV[i]], 
				&hash_key, &hash_val, 0);

			for (int j = i; j < R_ARGC; j++) {
				cmdargs.r_argv[j] = cmdargs.r_argv[j+1];
				cmdargs.r_argv_arg1[j] =
					cmdargs.r_argv_arg1[j+1];
				cmdargs.r_argv_arg2[j] =
					cmdargs.r_argv_arg2[j+1];
				cmdargs.r_argv_arg3[j] =
					cmdargs.r_argv_arg3[j+1];
				cmdargs.r_argv_delim[j] =
					cmdargs.r_argv_delim[j+1];
			}
			for (int k = 1; k <= R_INDEX_MAX; k++) {
				if (cmdargs.r_index_to_argv[k] >= i)
					cmdargs.r_index_to_argv[k] -= 1;
					
			}
			if (i == R_ARGC) {
				cmdargs.r_argv_arg1[R_ARGC] = NULL;
				cmdargs.r_argv_arg2[R_ARGC] = NULL;
				cmdargs.r_argv_arg3[R_ARGC] = NULL;
				cmdargs.r_argv_delim[R_ARGC] = '\0';
			}
			--R_ARGC;
			--i;
		}
	}

	char *refs[1+R_INDEX_MAX], *p, *p2;
	int refindex, num;
	FILEPROCESS_RETU

	exit(EX_OK);
}
