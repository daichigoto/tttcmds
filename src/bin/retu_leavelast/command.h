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

#define VERSION "20170228"
#define CMDNAME "retu_leavelast"
#define ALIAS "leavelast col_leavelast"

#include "ttt.h"

#define TGT_GYO_PROCESS(BUF,NF) \
	if (firstline) { \
		COPY_BUF_TO_DATAP(BUF,NF) \
		firstline = 0; \
	} \
	else { \
		for (i = 1; i < nf; i++) { \
			if (R_INDEX_EXIST[i]) { \
				if (0 == strcmp(BUF[i], data_p[i])) \
					printf("@ "); \
				else \
					printf("%s ", data_p[i]); \
			} \
			else \
				printf("%s ", data_p[i]); \
		} \
		if (0 != nf) { \
			if (R_INDEX_EXIST[nf]) { \
				if (0 == strcmp(BUF[nf], data_p[nf])) \
					printf("@\n"); \
				else \
					printf("%s\n", data_p[nf]); \
			} \
			else \
				printf("%s\n", data_p[nf]); \
			COPY_BUF_TO_DATAP(BUF,NF) \
		} \
	}

#define COPY_BUF_TO_DATAP(BUF,NF) { \
	nf = NF; \
	data_p = calloc(1, (NF + 1) * sizeof(char *)); \
	for (i = 1; i <= NF; i++) { \
		data_p[i] = calloc(1, sizeof(char) * strlen(BUF[i]+1)); \
		strcpy(data_p[i], BUF[i]); \
	} \
}

#define PRINT_LASTLINE { \
	for (i = 1; i < nf; i++) \
		printf("%s ", data_p[i]); \
	if (0 != nf) \
		printf("%s\n", data_p[nf]); \
}
