/*
 * Copyright (c) 2016 Daichi GOTO
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

#define VERSION "20161118"
#define CMDNAME "retu_numformat"
#define ALIAS "numformat"

#include "ttt.h"

#define TGT_RETU_PROCESS(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \
	if ('@' == RETU_BUFFER[0] && '\0' == RETU_BUFFER[1]) \
		putchar('@'); \
	else { \
		fmt = R_ARGV_ARG1[R_INDEX_TO_ARGV[INDEX]]; \
		num = strtod(RETU_BUFFER, (char **)NULL); \
		if (0 == num && \
			!('0' == RETU_BUFFER[0] && \
			 '\0' == RETU_BUFFER[1])) { \
			printf("%s",RETU_BUFFER); \
		} \
		else { \
			snprintf(str, BUFSIZE_FOR_DOUBLE, fmt, num); \
			str2ssvstr(ssvstr, str); \
			printf("%s", ssvstr); \
		} \
	}

#define NOTGT_RETU_PROCESS(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \
	printf("%s",RETU_BUFFER);

#define END_OF_LINE_RETU_PROCESS
