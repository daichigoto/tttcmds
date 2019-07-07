/*
 * Copyright (c) 2016-2019 Daichi GOTO
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

#define VERSION "20181214"
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
		str = calloc(str_len, sizeof(char)); \
		str2_len = str_len * 7; \
		if (NULL != str2) \
			free(str2); \
		str2 = calloc(str2_len, sizeof(char)); \
	} \
	if (buf_len < fmt_len + str_len) { \
		buf_len = fmt_len + str_len; \
		if (NULL != buf) \
			free(buf); \
		buf = calloc(buf_len + 1, sizeof(char)); \
		buf2_len = buf_len * 7; \
		if (NULL != buf2) \
			free(buf2); \
		buf2 = calloc(buf2_len + 1, sizeof(char)); \
	} \
	if (ssvstr_len < 2 * (fmt_len + str_len)) { \
		ssvstr_len = 2 * (fmt_len + str_len); \
		if (NULL != ssvstr) \
			free(ssvstr); \
		ssvstr = calloc(ssvstr_len + 1, sizeof(char)); \
		ssvstr2_len = ssvstr_len * 7; \
		if (NULL != ssvstr2) \
			free(ssvstr2); \
		ssvstr2 = calloc(ssvstr2_len + 1, sizeof(char)); \
	} \
	if (html5entity[R_INDEX_TO_ARGV[INDEX]]) { \
		ssvstr2str(str, RETU_BUFFER); \
		STR_TO_HTML5ENTITY(str,str2); \
		snprintf(buf2, buf2_len + 1, fmt, str2); \
		str2ssvstr(ssvstr2, buf2); \
		printf("%s", ssvstr2); \
	} \
	else { \
		ssvstr2str(str, RETU_BUFFER); \
		snprintf(buf, buf_len + 1, fmt, str); \
		str2ssvstr(ssvstr, buf); \
		printf("%s", ssvstr); \
	}

#define HOGE(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \

#define NOTGT_RETU_PROCESS(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \
	printf("%s",RETU_BUFFER);

#define END_OF_LINE_RETU_PROCESS

#define STR_TO_HTML5ENTITY(STR,STR2) \
	p = STR; \
	p2 = STR2; \
	while ('\0' != *p) { \
		switch (*p) { \
		case ' ': \
			++p; \
			*p2++ = '&'; \
			*p2++ = 'n'; \
			*p2++ = 'b'; \
			*p2++ = 's'; \
			*p2++ = 'p'; \
			*p2++ = ';'; \
			break; \
		case '<': \
			++p; \
			*p2++ = '&'; \
			*p2++ = 'l'; \
			*p2++ = 't'; \
			*p2++ = ';'; \
			break; \
		case '>': \
			++p; \
			*p2++ = '&'; \
			*p2++ = 'g'; \
			*p2++ = 't'; \
			*p2++ = ';'; \
			break; \
		case '\'': \
			++p; \
			*p2++ = '&'; \
			*p2++ = 'a'; \
			*p2++ = 'p'; \
			*p2++ = 'o'; \
			*p2++ = 's'; \
			*p2++ = ';'; \
			break; \
		case '"': \
			++p; \
			*p2++ = '&'; \
			*p2++ = 'q'; \
			*p2++ = 'u'; \
			*p2++ = 'o'; \
			*p2++ = 't'; \
			*p2++ = ';'; \
			break; \
		case '`': \
			++p; \
			*p2++ = '&'; \
			*p2++ = 'g'; \
			*p2++ = 'r'; \
			*p2++ = 'a'; \
			*p2++ = 'v'; \
			*p2++ = 'e'; \
			*p2++ = ';'; \
			break; \
		case '=': \
			++p; \
			*p2++ = '&'; \
			*p2++ = 'e'; \
			*p2++ = 'q'; \
			*p2++ = 'u'; \
			*p2++ = 'a'; \
			*p2++ = 'l'; \
			*p2++ = 's'; \
			*p2++ = ';'; \
			break; \
		default: \
			*p2++ = *p++; \
			break; \
		} \
	} \
	*p2 = '\0';
