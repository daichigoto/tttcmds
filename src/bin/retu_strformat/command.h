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

#define VERSION "20170407"
#define CMDNAME "retu_strformat"
#define ALIAS "strformat strfmt"

#include "ttt.h"

#define TGT_RETU_PROCESS(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \
	fmt = R_ARGV_ARG1[R_INDEX_TO_ARGV[INDEX]]; \
	fmt_len = strlen(fmt); \
	BUF_len = strlen(RETU_BUFFER); \
	if (str_len < BUF_len) { \
		str_len = BUF_len * 2; \
		if (NULL != str) \
			free(str); \
		str = calloc(1, sizeof(char) * str_len); \
	} \
	if (buf_len < fmt_len + str_len) { \
		buf_len = fmt_len + str_len; \
		if (NULL != buf) \
			free(buf); \
		buf = calloc(1, sizeof(char) * buf_len + 1); \
	} \
	if (ssvstr_len < 2 * (fmt_len + str_len)) { \
		ssvstr_len = 2 * (fmt_len + str_len); \
		if (NULL != ssvstr) \
			free(ssvstr); \
		ssvstr = calloc(1, sizeof(char) * ssvstr_len + 1); \
	} \
	ssvstr2str(str, RETU_BUFFER); \
	snprintf(buf, buf_len + 1, fmt, str); \
	str2ssvstr(ssvstr, buf); \
	printf("%s", ssvstr); \

#define NOTGT_RETU_PROCESS(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \
	printf("%s",RETU_BUFFER);

#define END_OF_LINE_RETU_PROCESS
