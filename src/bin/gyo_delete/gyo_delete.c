/*
 * Copyright (c) 2016,2017,2019,2021 Daichi GOTO
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
	getcmdargs(argc, argv, "a!o!1nNe@:shvD", 
	           CMDARGS_R_NEED|
		   CMDARGS_R_ARGARG_TO_SSVSTR|
		   CMDARGS_R_MINIMUMNUM_IS_0);

	/*
	 * Simple Equality/Inequality Condition
	 */
	if (FLAG_s) {
		simple_comparison();	 	
		exit(EX_OK);
	}

	/*
	 * Process option -@
	 */
	int match_or_not = 1;
	int nf = 0;
	char *val = "@";
	if (FLAG_AT)
		val = _str2ssvstr(FLAG_AT_ARG);

	/*
	 * hashtable setup for join process
	 */
	struct tttcmdargs cmdargs_org;
	char *r_argv[4];

	DB *btrees[R_ARGC + 1];
	DBT b_key, b_val;
	memset(btrees, 0, (R_ARGC + 1) * sizeof(DB *));

	int match_count = 1;
	while (NULL != R_ARGV_ARG1[match_count])
		++match_count;
	--match_count;

	cmdargs_org = cmdargs;

	for (int i = 1; i <= match_count; i++) {
		if (0 == cmdargs_org.r_argv[i])
			usage();

		if (NULL == cmdargs_org.r_argv_arg2[i]) {
			btrees[i] = NULL;
			continue;
		}

		r_argv[0] = "";
		r_argv[1] = cmdargs_org.r_argv_arg2[i];
		r_argv[2] = _ssvstr2str(cmdargs_org.r_argv_arg1[i]);
		r_argv[3] = NULL;
		getcmdargs(3, r_argv, "", CMDARGS_R_NEED);

		btrees[i] = dbopen(NULL, O_CREAT | O_RDWR, 0, DB_BTREE, NULL);
		if (NULL == btrees[i])
			err(errno, CMDNAME ": dbopen failed");

		FILEPROCESS_RETU
	}

	/*
	 * restore command cmdargs
	 */
	cmdargs = cmdargs_org;

	long long int n1, n2[1+R_ARGC];
	if (FLAG_N)
		for (int i = 1; i <= match_count; i++) {
			errno = 0;
			n2[i] = strtoll(R_ARGV_ARG1[i], (char **)NULL, 10);
			if (EINVAL == errno)
				usage();
		}

	int cmpret;
	int first_line = 1;
	FILEPROCESS_GYO

	if (FLAG_n)
		exit(match_or_not);

	if (FLAG_e && match_or_not) {
		if (R_ARGC == match_count) {
			for (int i = 1; i < nf; i++)
				printf("%s ", val);
			printf("%s\n", val);
		}
		else {
			for (int i = match_count+1; i < R_ARGC; i++)
				printf("%s ", val);
			printf("%s\n", val);
		}
	}

	exit(EX_OK);
}
