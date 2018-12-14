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
	getcmdargs(argc, argv, "hvD",
	           CMDARGS_R_NEED|CMDARGS_R_ARGARG_1_NEED);

	char *str, *str2, *ssvstr, *ssvstr2, *fmt, *buf, *buf2, *p, *p2;
	int str_len, str2_len, ssvstr_len, ssvstr2_len, fmt_len, 
		buf_len, buf2_len, BUF_len;

	int html5entity[1+R_ARGC];
	for (int i = 1; i <= R_ARGC; i++) {
		if (NULL == (p = strstr(R_ARGV_ARG1[i], "%h"))) 
			html5entity[i] = 0;
		else {
			*(p + 1) = 's';
			html5entity[i] = 1;
		}
	}

	if (FLAG_D) {
		for (int i = 1; i <= R_ARGC; i++)
			fprintf(stderr, "html5entity[%d]: %d\n", 
				i, html5entity[i]);
		fprintf(stderr, "\n");
		for (int i = 1; i <= R_ARGC; i++)
			fprintf(stderr, "R_ARGV_ARG1[%d]: %s\n", 
				i, R_ARGV_ARG1[i]);
	}

	str = str2 = ssvstr = ssvstr2 = NULL;
	fmt = buf = buf2 = p = p2 = NULL;

	str_len = str2_len = ssvstr_len = ssvstr2_len = 0;
	fmt_len = buf_len = buf2_len = BUF_len = 0;

	FILEPROCESS_RETU

	exit(EX_OK);
}
