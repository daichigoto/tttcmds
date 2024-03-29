/*
 * Copyright (c) 2016,2017,2023 Daichi GOTO
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

#define VERSION "20230323"
#define CMDNAME "retu_diff"
#define ALIAS "retudiff col_diff"

#include "ttt.h"

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	if (0 != NF) { \
		p_ssvline = &ssv_firstline; \
		if (0 == p_ssvline->nf) \
			goto print; \
		do { \
			for (int i = 1; i <= R_ARGC; i++) { \
				if (0 != strcmp( \
					p_ssvline->data[R_ARGV[i]], \
					GYO_BUFFER[R_ARGV[i]])) \
					break; \
				if (R_ARGC == i) \
					goto gyo_match; \
			} \
			p_ssvline = p_ssvline->next; \
		} \
		while (NULL != p_ssvline); \
	} \
print: \
	if (0 != NF) { \
		for (int i = 1; i < NF; i++) \
			printf("%s ", GYO_BUFFER[i]); \
		printf("%s\n", GYO_BUFFER[NF]); \
	} \
gyo_match:
