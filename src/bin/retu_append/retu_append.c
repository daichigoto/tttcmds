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
	getcmdargs(argc, argv, "d:rhvD",
	           CMDARGS_R_NEED|CMDARGS_R_ARGARG_1_NEED);

	char *delim = "";
	int delim_len = 0;
	if (FLAG_d) {
		delim = _str2ssvstr(FLAG_d_ARG);
		delim_len = strlen(delim);
	}

	int appcols[R_ARGC+1], appnum = 1, match;
	for (int i = 1; i <= R_ARGC; i++) {
		errno = 0;
		appcols[i] = 
			(int)strtol(R_ARGV_ARG1[i], (char **)NULL, 10);
		match = 0;
		for (int j = 1; j < i; j++)
			if (appcols[j] == appcols[i])
				match = 1;
		if (!match)
			++appnum;
			
		if (EINVAL == errno)
			usage();
	}

	char *buf, *buf_p;
	int len1, len2, spacenum;
	FILEPROCESS_GYO

	exit(EX_OK);
}
