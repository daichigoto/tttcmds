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
	getcmdargs(argc, argv, "1N@:hvD", CMDARGS_R_NEED);

	char min[R_ARGC+1][4096];
	int num;
	int nummin[R_ARGC+1];
	int numinc[R_ARGC+1];
	char *numfmt[R_ARGC+1];

	for (int i = 1; i <= R_ARGC; i++) {
		min[i][0] = '@';
		min[i][1] = '\0';
		nummin[i] = 0;
		numinc[i] = 0;
		numfmt[i] = "%d";
		if (NULL != R_ARGV_ARG1[i]) {
			errno = 0;
			numinc[i] = (int)strtol(R_ARGV_ARG1[i],
				(char **)NULL, 10);
			if (EINVAL == errno)
				usage();
		}
		if (NULL != R_ARGV_ARG2[i])
			numfmt[i] = R_ARGV_ARG2[i];
	}
	int first_line = 1;

	FILEPROCESS_GYO

#define PRINT_VALUE(I,DELIMITER) \
	if (FLAG_AT) { \
		if ('@' == min[I][0] && '\0' == min[I][1]) \
			printf("%s%s", _str2ssvstr(FLAG_AT_ARG), \
				DELIMITER); \
		else \
			printf("@%s", DELIMITER); \
	} else { \
		if (FLAG_N && NULL != R_ARGV_ARG1[I]) { \
			printf(numfmt[I], nummin[I] + numinc[I]); \
			printf("%s", DELIMITER); \
		} \
		else \
			printf("%s%s", min[I], DELIMITER); \
	}

	for (int i = 1; i < R_ARGC; i++) {
		PRINT_VALUE(i, " ")
	}
	PRINT_VALUE(R_ARGC, "\n")

	exit(EX_OK);
}
