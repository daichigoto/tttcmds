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
#define CMDNAME "conv_ssv2ssv"
#define ALIAS "ssv2ssv"

#include "ttt.h"

#define TGT_CHAR_PROCESS(C) \
	if (C == ' ') \
		++retu; \
	else if ((C == '\n') || \
	         (C == EOF && (p != '\n' && p != EOF)) || \
		 (C == EOF && p == EOF)) { \
		if (C == EOF && p == EOF) \
			retu = 0; \
		else \
			++retu; \
		if ((C == EOF && p == EOF && -1 == retumax) || \
		    retumax < retu) \
			retumax = retu; \
		retu = 0; \
	} \
	p = C;

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	col = 1; \
	if (FILEPROCESS_GYO_FILESIZE_IS_ZERO) \
		goto tgt_gyo_process_end; \
	if (FLAG_w) { \
		j = 0; \
		for (i = 1; i <= NF; i++) { \
			PRINT_COLNUMBER \
			printf("%s", GYO_BUFFER[i]); \
			++j; \
			if (j == wrap) { \
				if (i != NF) { \
					j = 0; \
					printf("\n"); \
				} \
			} \
			else \
				printf(" "); \
		} \
		++j; \
		while (j < wrap) { \
			PRINT_COLNUMBER \
			printf("@ "); \
			++j; \
		} \
		if (j == wrap) { \
			PRINT_COLNUMBER \
			printf("@"); \
		} \
		printf("\n"); \
	} \
	else { \
		for (i = 1; i < retumax; i++) { \
			PRINT_COLNUMBER \
			if (i > NF) \
				printf("@ "); \
			else \
				printf("%s ", GYO_BUFFER[i]); \
		} \
		if (retumax != 0) { \
			PRINT_COLNUMBER \
			if (i > NF) \
				printf("@\n"); \
			else \
				printf("%s\n", GYO_BUFFER[retumax]); \
		} \
	} \
tgt_gyo_process_end:

#define PRINT_COLNUMBER \
	if (FLAG_n) { \
		printf("%d:", col++); \
	}
