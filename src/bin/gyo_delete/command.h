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
#define CMDNAME "gyo_delete"
#define ALIAS "gyodel row_delete"

#include "ttt.h"

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	if (!FLAG_o) { \
		if (NF < R_ARGV_MAX) \
			goto gyo_not_match; \
		for (int i = 1; i <= R_ARGC; i++) \
			if (R_INDEX_EXIST[R_ARGV[i]] == \
			    R_INDEX_IS_EXISTENCE) { \
				cmpret = strcmp(GYO_BUFFER[R_ARGV[i]], \
					R_ARGV_ARG1[i]); \
				switch (R_ARGV_DELIM[i]) { \
				case '>': \
					if (cmpret <= 0) \
						goto gyo_not_match; \
					break; \
				case '<': \
					if (cmpret >= 0) \
						goto gyo_not_match; \
					break; \
				default: \
					if (0 != cmpret) \
						goto gyo_not_match; \
					break; \
				} \
			} \
		goto gyo_match; \
	} \
	else { \
		for (int i = 1; i <= R_ARGC; i++) { \
			if (R_INDEX_EXIST[R_ARGV[i]] == \
			    R_INDEX_IS_EXISTENCE) { \
				cmpret = strcmp(GYO_BUFFER[R_ARGV[i]], \
					R_ARGV_ARG1[i]); \
				switch (R_ARGV_DELIM[i]) { \
				case '>': \
					if (cmpret > 0) \
						goto gyo_match; \
					break; \
				case '<': \
					if (cmpret < 0) \
						goto gyo_match; \
					break; \
				default: \
					if (0 == cmpret) \
						goto gyo_match; \
					break; \
				} \
			} \
		} \
		goto gyo_not_match; \
	} \
gyo_not_match: \
	for (int i = 1; i < NF; i++) \
		printf("%s ", GYO_BUFFER[i]); \
	printf("%s\n", GYO_BUFFER[NF]); \
gyo_match:
