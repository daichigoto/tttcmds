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

#define VERSION "20170902"
#define CMDNAME "conv_ssv2transposedssv"
#define ALIAS "transpose"

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
	if (! (FILEPROCESS_GYO_FILESIZE_IS_ZERO)) { \
		p_ssvline->next = calloc(1, sizeof(struct ssvline)); \
		p_ssvline = p_ssvline->next; \
		p_ssvline->outputed = 0; \
		p_ssvline->nf = retumax; \
		p_ssvline->data = \
			calloc(1, sizeof(char *) * (p_ssvline->nf + 1)); \
		for (int i = 1; i <= retumax; i++) { \
			if (i > NF) { \
				p_ssvline->data[i] = calloc(1, 2); \
				p_ssvline->data[i][0] = '@'; \
				p_ssvline->data[i][1] = '\0'; \
			} \
			else { \
				p_ssvline->data[i] = \
					calloc(1, sizeof(char) * \
					(strlen(GYO_BUFFER[i]) + 1)); \
				strcpy(p_ssvline->data[i], \
					GYO_BUFFER[i]); \
			} \
		} \
	}
