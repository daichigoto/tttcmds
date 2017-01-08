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

#define VERSION "20170109"
#define CMDNAME "conv_ssv2txt"
#define ALIAS "ssv2txt"

#include "ttt.h"

/*
 * count the max length for each column
 */
#define TGT_CHAR_PROCESS(C) \
	if (C == ' ') \
		++i; \
	else if ((C == '\n') || \
	         (C == EOF && (p != '\n' && p != EOF)) || \
		 (C == EOF && p == EOF)) { \
		if (C == EOF && p == EOF) \
			i = 0; \
		else \
			++i; \
		if ((C == EOF && p == EOF && -1 == retu) || \
		    retu != i) \
		    	if (retu < i) \
				retu = i; \
		i = 0; \
	} \
	p = C;

/*
 * count the max length for each column
 */
#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	for (i = 1; i <= NF; i++) { \
		len = ssvstr2str_len(GYO_BUFFER[i]); \
		if (maxlen[i] < len) \
			maxlen[i] = len; \
	}

/*
 * convert the ssv data to the text table data
 */
#define NOTGT_RETU_PROCESS(BUF,BUFLEN,I) \
	ssvstr2str(buf[I], BUF); \
	len = strlen(buf[I]); \
	count = maxlen[I] - len; \
	for (i = 0; i < count; i++) \
		putchar(' '); \
	printf("%s", buf[I]);

#define TGT_RETU_PROCESS(BUF,BUFLEN,I)

#define END_OF_LINE_RETU_PROCESS

/*
 * convert the ssv data to the text data
 */
#define TGT_BUFFER_PROCESS(BUF,BUFLEN) \
	printf("%s",_ssvstr2str(BUF));
