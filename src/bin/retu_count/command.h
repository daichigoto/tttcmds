/*
 * Copyright (c) 2016 Daichi GOTO
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

#define VERSION "20161103"
#define CMDNAME "retu_count"
#define ALIAS "retu col_count"

#include "ttt.h"

#define TGT_CHAR_PROCESS(C) \
	if (C == ' ') \
		++retu; \
	else if ((C == '\n') || \
	         (C == EOF && (p != '\n' && p != EOF)) || \
		 (C == EOF && p == EOF)) { \
		if (C == EOF && p == EOF) { \
			filenum = 0; \
			retu = 0; \
		} \
		else { \
			++allnum; \
			++filenum; \
			++retu; \
		} \
		if ((C == EOF && p == EOF && -1 == preretu) || \
		    preretu != retu) { \
			if (!FLAG_f && !FLAG_n) \
				printf("%d\n", retu); \
			else if (!FLAG_f && FLAG_n) \
				printf("%d: %d\n", allnum, retu); \
			else if (FLAG_f && !FLAG_n) \
				printf("%s:%d: %d\n", \
				       F_ARGV[fp_file_i], filenum, retu); \
			else if (FLAG_f && FLAG_n) \
				printf("%s:%d:%d: %d\n", \
				       F_ARGV[fp_file_i], filenum, \
				       allnum, retu); \
			preretu = retu; \
		} \
		retu = 0; \
	} \
	if (C == EOF) \
		filenum = 0; \
	p = C;
