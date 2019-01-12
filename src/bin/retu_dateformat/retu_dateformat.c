/*
 * Copyright (c) 2017-2019 Daichi GOTO
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
	getcmdargs(argc, argv, "3:ehvD",
	           CMDARGS_R_NEED|
		   CMDARGS_R_ARGARG_1_NEED|
		   CMDARGS_R_ARGARG_2_NEED);

	/*
	 * Column number used as comparison basis for 30 hours
	 */
	int index_30hbase = 0;
	if (FLAG_3) {
		errno = 0;
		index_30hbase = (int)strtol(FLAG_3_ARG, (char **)NULL, 10);
                if (EINVAL == errno)
                        usage();
	}
	if (FLAG_D)
		fprintf(stderr, "index_30hbase: %d\n", index_30hbase);

	int str_len, ssvstr_len, outfmt_len, index, indexH, 
		hours30_output = 0, H, loopend = 0;
	char *str, *ssvstr, *p, *ptr, *ptr2, *p_base, 
		basedate[9], tgtdate[9], tgtH[3], varry[4] = "+0d";
	time_t tval;
	struct tm tm, tm_tomorrow;
	struct vary *v = NULL;

	(void) setlocale(LC_TIME, "");
	time(&tval);
	tm = *localtime(&tval);
	strptime("000000", "%H%M%S", &tm);
	tm_tomorrow = tm;

	str_len = ssvstr_len = BUFFER_SIZE;
	str = calloc(1, str_len * sizeof(char));
	ssvstr = calloc(1, ssvstr_len * sizeof(char));

	FILEPROCESS_GYO

	exit(EX_OK);
}
