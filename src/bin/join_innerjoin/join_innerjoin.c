/*
 * Copyright (c) 2017,2023 Daichi GOTO
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
	getcmdargs(argc, argv, "rhvD",
	           CMDARGS_R_NEED|
		   CMDARGS_F_NEED|
		   CMDARGS_STDIN_TO_TMPFILE);

	int rightkeys[R_ARGC+1], rightoutnum = 0, rightnf;
	int match, match1, match2, spaces;
	for (int i = 1; i <= R_ARGC; i++) {
		errno = 0;
		rightkeys[i] =
			(int)strtol(R_ARGV_ARG1[i], (char **)NULL, 10);
		match = 0;
		for (int j = 1; j < i; j++)
			if (rightkeys[j] == rightkeys[i])
				match = 1;
		if (!match)
			++rightoutnum;
		if (EINVAL == errno)
			usage();
	}

	if (2 != F_ARGC)
		usage();

	struct ssvline ssv_firstline;
	struct ssvline *p_ssvline;
	ssvfile2ssvlines(F_ARGV[2], &ssv_firstline);
	F_ARGC = 1;
	FILEPROCESS_GYO

	getcmdargs_unlinktmpf();

	exit(EX_OK);
}
