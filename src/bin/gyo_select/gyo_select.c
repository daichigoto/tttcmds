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
	getcmdargs(argc, argv, "a!o!1nNhvD",
	           CMDARGS_R_NEED|
		   CMDARGS_R_ARGARG_1_NEED|
		   CMDARGS_R_ARGARG_TO_SSVSTR);

	int match_or_not = 1;

	/*
	 * hashtable setup for join process
	 */
	struct tttcmdargs cmdargs_org;
	char *r_argv[4];

	DB *hashtables[R_ARGC + 1];
	DBT hash_key, hash_val;
	memset(hashtables, 0, (R_ARGC + 1) * sizeof(DB *));
	
	cmdargs_org = cmdargs;

	for (int i = 1; i <= cmdargs_org.r_argc; i++) {
		if (NULL == cmdargs_org.r_argv_arg2[i]) {
			hashtables[i] = NULL;
			continue;
		}

		r_argv[0] = "";
		r_argv[1] = cmdargs_org.r_argv_arg2[i];
		r_argv[2] = _ssvstr2str(cmdargs_org.r_argv_arg1[i]);
		r_argv[3] = NULL;
		getcmdargs(3, r_argv, "", CMDARGS_R_NEED);

		hashtables[i] = dbopen(NULL, O_CREAT|O_RDWR, 0644,
			DB_HASH, NULL);
		if (NULL == hashtables[i])
			err(errno, "retu_assign: dbopen failed");

		FILEPROCESS_RETU
	}

	/*
	 * restore command cmdargs
	 */
	cmdargs = cmdargs_org;

	long long int n1, n2[1+R_ARGC];
	if (FLAG_N)
		for (int i = 1; i <= R_ARGC; i++) {
			n2[i] = strtoll(R_ARGV_ARG1[i], (char **)NULL, 10);
			if (0 == n2[i] && EINVAL == errno)
				usage();
		}

	int cmpret;
	int first_line = 1;
	FILEPROCESS_GYO

	if (FLAG_n)
		exit(match_or_not);

	exit(EX_OK);
}
