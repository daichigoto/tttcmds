/*
 * Copyright (c) 2016,2017,2019 Daichi GOTO
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

#define VERSION "20170911"
#define CMDNAME "embed_ssv1txt"
#define ALIAS "ssv1txt"

#include <fcntl.h>

#include "ttt.h"

struct swaprules {
	int r;
	char *r_arg;
	struct swaprules *next;
};

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	if (FLAG_m) \
		m = max; \
	for (int j = 0; j < tsize; j++) { \
		match = 0; \
		if (!FLAG_m || (FLAG_m && m > 0)) { \
			for (int i = 1; i <= R_ARGC; i++) { \
				len = strlen(R_ARGV_ARG1[i]); \
				if (0 == strncmp(R_ARGV_ARG1[i], \
					tbuf + j, len)) { \
					if (R_ARGV[i] <= NF) { \
						PRINTOUT(GYO_BUFFER) \
					} \
					if (FLAG_m) \
						--m; \
					j += len - 1; \
					match = 1; \
					break; \
				} \
			} \
		} \
		if (!match) \
			putchar(*(tbuf + j)); \
	}	

#define PRINTOUT(GYO_BUFFER) \
	if (!FLAG_b) { \
	 	printf("%s", _ssvstr2str(GYO_BUFFER[R_ARGV[i]])); \
	} \
	else { \
		bbuf_p1 = GYO_BUFFER[R_ARGV[i]]; \
		bbuf = calloc(1 + strlen(bbuf_p1), sizeof(char)); \
		bbuf_p2 = bbuf; \
		while ('\0' != *bbuf_p1) { \
			switch (*bbuf_p1) { \
			case '\\': \
				++bbuf_p1; \
				switch (*bbuf_p1) { \
				case '\\': \
					*bbuf_p2 = '\\'; \
					++bbuf_p1; \
					++bbuf_p2; \
					break; \
				case 'n': \
					*bbuf_p2 = '\n'; \
					++bbuf_p1; \
					++bbuf_p2; \
					break; \
				case 'r': \
					++bbuf_p1; \
					break; \
				default: \
					*bbuf_p2 = '\\'; \
					++bbuf_p2; \
					*bbuf_p2 = *bbuf_p1; \
					++bbuf_p1; \
					++bbuf_p2; \
					break; \
				} \
				break; \
			case '_': \
				*bbuf_p2 = ' '; \
				++bbuf_p1; \
				++bbuf_p2; \
				break; \
			default: \
				*bbuf_p2 = *bbuf_p1; \
				++bbuf_p1; \
				++bbuf_p2; \
				break; \
			} \
		} \
	 	printf("%s", _ssvstr2str(bbuf)); \
		free(bbuf); \
	}
