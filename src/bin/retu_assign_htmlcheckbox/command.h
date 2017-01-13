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

#define VERSION "20170113"
#define CMDNAME "retu_assign_htmlcheckbox"
#define ALIAS "assign_htmlcheckbox col_assign_htmlcheckbox"

#include "ttt.h"
#include "./../retu_assign/retu_assign.h"

/*
 * value to HTML CHECKBOX conversion
 */
#define TGT_RETU_PROCESS(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \
	if (FLAG_r) \
		COPY_RETUBUFFER_TO_REFS(RETU_BUFFER,INDEX) \
	if (0 == strcmp("@", ssvval)) \
		printf("<input_type=\"checkbox\"_value=\"\""); \
	else if (0 == strcmp("\\@", ssvval)) \
		printf("<input_type=\"checkbox\"_value=\"@\""); \
	else \
		printf("<input_type=\"checkbox\"_value=\"%s\"", \
			_quote2charref(ssvval)); \
	if (0 == hashtables[INDEX]->seq( \
		hashtables[INDEX], &hash_key, &hash_val, R_FIRST)) { \
		if (FLAG_r) \
			PRINT_REFERENCED_STRING(INDEX) \
		else \
			printf("_%s=\"%s\"", hash_key.data, \
				_quote2charref(hash_val.data)); \
	} \
	while (0 == hashtables[INDEX]->seq( \
		hashtables[INDEX], &hash_key, &hash_val, R_NEXT)) { \
		if (FLAG_r) \
			PRINT_REFERENCED_STRING(INDEX) \
		else \
			printf("_%s=\"%s\"", hash_key.data, \
				_quote2charref(hash_val.data)); \
	} \
	if (0 == strcmp(ssvval, RETU_BUFFER)) \
		printf("_checked"); \
	printf(">");

#define NOTGT_RETU_PROCESS(RETU_BUFFER,RETU_BUFFER_MAXLEN,INDEX) \
	if (FLAG_r) \
		COPY_RETUBUFFER_TO_REFS(RETU_BUFFER,INDEX) \
	printf("%s",RETU_BUFFER);

#define COPY_RETUBUFFER_TO_REFS(RETU_BUFFER,INDEX) { \
	refs[INDEX] = \
		calloc(1, (1 + strlen(RETU_BUFFER)) * sizeof(char)); \
	strcpy(refs[INDEX],RETU_BUFFER); \
}

#define PRINT_REFERENCED_STRING(INDEX) { \
	printf("_%s=\"", hash_key.data); \
	p = hash_val.data; \
	while ('\0' != *p) { \
		if ('\\' != *p) \
			putchar(*p); \
		else { \
			++p; \
			num = (int)(*p) - 48; \
			if (num < 0 || 9 < num) \
				putchar(*p); \
			else { \
				refindex = 0; \
				for (;;) { \
					refindex = \
						10 * refindex + num; \
					num = (int)(*(p+1)) - 48; \
					if (num < 0 || 9 < num) \
						break; \
					++p; \
				} \
			} \
			if (0 == refindex || \
				refindex > INDEX) \
				usage(); \
			p2 = _quote2charref(refs[refindex]); \
			if (0 == strcmp("@", p2)) \
				; \
			else if (0 == strcmp("\\@", p2)) \
				putchar('@'); \
			else \
				printf("%s", p2); \
		} \
		++p; \
	} \
	putchar('"'); \
}

#define END_OF_LINE_RETU_PROCESS
