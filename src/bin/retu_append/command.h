/*
 * Copyright (c) 2017 Daichi GOTO
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

#define VERSION "20170827"
#define CMDNAME "retu_append"
#define ALIAS "append col_append"

#include "ttt.h"

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	for (int i = 1; i <= R_ARGC; i++) { \
		len1 = strlen(GYO_BUFFER[R_ARGV[i]]); \
		len2 = strlen(GYO_BUFFER[appcols[i]]); \
		if (0 != strcmp("@", GYO_BUFFER[R_ARGV[i]]) && \
		    0 != strcmp("@", GYO_BUFFER[appcols[i]]) ) { \
		    	buf = calloc(1, len1 + delim_len + len2 + 1); \
			buf_p = buf; \
			memcpy(buf_p, GYO_BUFFER[R_ARGV[i]], len1); \
			buf_p += len1; \
			memcpy(buf_p, delim, delim_len); \
			buf_p += delim_len; \
			memcpy(buf_p, GYO_BUFFER[appcols[i]], len2); \
			GYO_BUFFER[R_ARGV[i]] = buf; \
		} \
		else if (0 == strcmp("@", GYO_BUFFER[R_ARGV[i]]) && \
		         0 != strcmp("@", GYO_BUFFER[appcols[i]]) ) { \
			buf = calloc(1, len2 + 1); \
			buf_p = buf; \
			memcpy(buf_p, GYO_BUFFER[appcols[i]], len2); \
			GYO_BUFFER[R_ARGV[i]] = buf; \
		} \
		else if (0 != strcmp("@", GYO_BUFFER[R_ARGV[i]]) && \
		         0 == strcmp("@", GYO_BUFFER[appcols[i]]) ) { \
			\
		} \
		else { \
			\
		} \
	} \
	spacenum = 0; \
	for (int i = 1; i <= NF; i++) { \
		match = 0; \
		if (FLAG_r) { \
			for (int j = 1; j <= R_ARGC; j++) { \
				if (i == appcols[j]) { \
					match = 1; \
					break; \
				} \
			} \
		} \
		if (!match) { \
			printf("%s", GYO_BUFFER[i]); \
			if (FLAG_r) { \
				if (spacenum < NF - appnum - 1) { \
					putchar(' '); \
					++spacenum; \
				} \
			} \
			else { \
				if (spacenum < NF - 1) { \
					putchar(' '); \
					++spacenum; \
				} \
			} \
		} \
	} \
	putchar('\n');
