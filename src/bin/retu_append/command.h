/*
 * Copyright (c) 2017,2021 Daichi GOTO
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

#define VERSION "20170915"
#define CMDNAME "retu_append"
#define ALIAS "append col_append"

#include "ttt.h"

#define NUM_CHECK(X) \
	if ((int)X < 48 || 57 < (int)X) { \
		usage(); \
	}

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	for (int i = 1; i <= R_ARGC; i++) { \
		len = strlen(GYO_BUFFER[R_ARGV[i]]); \
		for (int j = 1; j <= appcols_len[i]; j++) { \
			if (appcols[i][j] > NF) \
				usage(); \
			len += delim_len; \
			len += strlen(GYO_BUFFER[appcols[i][j]]); \
		} \
		buf[i] = calloc(len + 1, sizeof(char)); \
	} \
	for (int i = 1; i <= R_ARGC; i++) { \
		buf_p = buf[i]; \
		if (0 != strcmp("@", GYO_BUFFER[R_ARGV[i]])) { \
			len = strlen(GYO_BUFFER[R_ARGV[i]]); \
			memcpy(buf_p, GYO_BUFFER[R_ARGV[i]], len); \
			buf_p += len; \
		} \
		for (int j = 1; j <= appcols_len[i]; j++) { \
			if (0 != strcmp("@", GYO_BUFFER[appcols[i][j]])) { \
				if ('\0' != buf[i][0]) { \
					memcpy(buf_p, delim, delim_len); \
					buf_p += delim_len; \
				} \
				len = strlen(GYO_BUFFER[appcols[i][j]]); \
				memcpy(buf_p, GYO_BUFFER[appcols[i][j]], \
					len); \
				buf_p += len; \
			} \
		} \
		if ('\0' == buf[i][0]) { \
			buf[i][0] = '@'; \
			buf[i][1] = '\0'; \
		} \
	} \
	spaces = NF - remcols_num - 1; \
	for (int i = 1; i <= NF; i++) { \
		if (FLAG_r) { \
			if (i > remcols_max || !remcols[i]) { \
				if (R_INDEX_EXIST[i]) { \
					printf("%s", \
						buf[R_INDEX_TO_ARGV[i]]); \
				} \
				else { \
					printf("%s", GYO_BUFFER[i]); \
				} \
				if (spaces > 0) { \
					putchar(' '); \
					--spaces; \
				} \
			} \
		} \
		else { \
			if (R_INDEX_EXIST[i]) { \
				printf("%s", buf[R_INDEX_TO_ARGV[i]]); \
			} \
			else { \
				printf("%s", GYO_BUFFER[i]); \
			} \
			if (i != NF) \
				putchar(' '); \
		} \
	} \
	for (int i = 1; i <= R_ARGC; i++) \
		free(buf[i]); \
	putchar('\n');
