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

#define VERSION "20170828"
#define CMDNAME "join_outerjoin"
#define ALIAS "outerjoin"

#include "ttt.h"

struct ssvline {
	char		**data;
	int		nf;
	struct ssvline	*next;
	int		outputed;
};

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	leftnf = NF; \
	match1 = 0; \
	if (0 != NF) { \
		p_ssvline = &ssv_firstline; \
		if (0 == p_ssvline->nf) { \
			match1 = 1; \
			LEFT_PRINT(GYO_BUFFER,NF); \
			putchar('\n'); \
		} \
		else \
			do { \
				rightnf = p_ssvline->nf; \
				for (int i = 1; i <= R_ARGC; i++) { \
					if (0 != strcmp( \
					    GYO_BUFFER[R_ARGV[i]], \
					    p_ssvline->data[rightkeys[i]])) \
						break; \
					if (R_ARGC == i) { \
						match1 = 1; \
						LEFT_PRINT(GYO_BUFFER,NF); \
						if (rightnf - \
						      rightoutnum > 0) { \
							putchar(' '); \
							RIGHT_PRINT; \
						} \
						putchar('\n'); \
					} \
				} \
				p_ssvline = p_ssvline->next; \
			} \
		while (NULL != p_ssvline); \
		if (!match1) { \
			LEFT_PRINT(GYO_BUFFER,NF); \
			if (rightnf - rightoutnum > 0) { \
				putchar(' '); \
				RIGHT_PRINT_NONE; \
			} \
			putchar('\n'); \
		} \
	} \

#define LEFT_PRINT(GYO_BUFFER,NF) \
	if (0 != NF) { \
		for (int j = 1; j < NF; j++) \
			printf("%s ", GYO_BUFFER[j]); \
		printf("%s", GYO_BUFFER[NF]); \
	}

#define RIGHT_PRINT \
	if (FLAG_r) { \
		spaces = rightnf - rightoutnum - 1; \
		for (int j = 1; j <= rightnf; j++) { \
			match2 = 0; \
			for (int k = 1; k <= R_ARGC; k++) { \
				if (j == rightkeys[k]) \
					match2 = 1; \
			} \
			if (!match2) { \
				printf("%s", p_ssvline->data[j]); \
				p_ssvline->outputed = 1; \
				if (spaces > 0) { \
					putchar(' '); \
					--spaces; \
				} \
			} \
		} \
	} \
	else { \
		for (int j = 1; j < p_ssvline->nf; j++) \
			printf("%s ", p_ssvline->data[j]); \
		printf("%s", p_ssvline->data[p_ssvline->nf]); \
		p_ssvline->outputed = 1; \
	}

#define RIGHT_PRINT_NONE \
	if (FLAG_r) { \
		spaces = rightnf - rightoutnum - 1; \
		for (int j = 1; j <= rightnf; j++) { \
			match2 = 0; \
			for (int k = 1; k <= R_ARGC; k++) { \
				if (j == rightkeys[k]) \
					match2 = 1; \
			} \
			if (!match2) { \
				printf("@"); \
				if (spaces > 0) { \
					putchar(' '); \
					--spaces; \
				} \
			} \
		} \
	} \
	else { \
		for (int j = 1; j < rightnf; j++) \
			printf("@ "); \
		printf("@"); \
	}
