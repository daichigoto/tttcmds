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

#define VERSION "20170217"
#define CMDNAME "retu_dateformat"
#define ALIAS "dateformat"

#ifdef __linux__
#define _XOPEN_SOURCE
typedef unsigned char u_char;
#endif

#include "ttt.h"

#define TGT_RETU_PROCESS(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \
	if (RETU_BUFFER_MAXLEN > str_len) { \
		free(str); \
		str_len = RETU_BUFFER_MAXLEN; \
		str = calloc(1, str_len * sizeof(char)); \
	} \
	/*
	 * The ssvstr's buffer length that str2ssvstr(ssvstr, str)
	 * requires is (strlen(str) * 2 + 1).
	 */ \
	outfmt_len = strlen(R_ARGV_ARG2[R_INDEX_TO_ARGV[INDEX]]); \
	if ((outfmt_len * 2) + 1 > ssvstr_len) { \
		free(ssvstr); \
		ssvstr_len = (outfmt_len * 2) + 1; \
		ssvstr = calloc(1, ssvstr_len * sizeof(char)); \
	} \
	if ('@' == RETU_BUFFER[0] && '\0' == RETU_BUFFER[1]) \
		putchar('@'); \
	else { \
		ssvstr2str(str, RETU_BUFFER); \
		if (NULL != strptime( \
				str,  \
				R_ARGV_ARG1[R_INDEX_TO_ARGV[INDEX]], \
				tm)) { \
			(void)strftime( \
				str, \
				str_len, \
				R_ARGV_ARG2[R_INDEX_TO_ARGV[INDEX]], \
				tm); \
			str2ssvstr(ssvstr, str); \
			printf("%s", ssvstr); \
		} \
		else { \
			printf("%s", RETU_BUFFER); \
		} \
	}

#define NOTGT_RETU_PROCESS(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \
	printf("%s",RETU_BUFFER);

#define END_OF_LINE_RETU_PROCESS
