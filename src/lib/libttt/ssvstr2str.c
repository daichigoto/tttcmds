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

#include "ttt.h"

char *
ssvstr2str(char *str, char *ssvstr)
{
	char *str_p, *ssvstr_p;
	str_p = str;
	ssvstr_p = ssvstr;

	if (NULL == ssvstr) {
		*str_p = '\0';
		return str;
	}
	if ('@' == *ssvstr_p && '\0' == *(ssvstr_p + 1)) {
		*str_p = '\0';
		return str;
	}
	if ('\\' == *ssvstr_p && '@' == *(ssvstr_p + 1) && 
		'\0' == *(ssvstr_p + 2)) {
		*str_p = '@';
		*(str_p + 1) = '\0';
		return str;
	}

	while (1) {
		switch (*ssvstr_p) {
		case '\\':
			switch (*(ssvstr_p + 1)) {
			case '@':
			case '_':
				*str_p = *(ssvstr_p + 1);
				++ssvstr_p;
				break;
			default:
				*str_p = '\\';
				break;
			}
			break;
		case '_':
			*str_p = ' ';
			break;
		case '\0':
			*str_p = '\0';
			goto finish;
		default:
			*str_p = *ssvstr_p;
			break;
		}
		++str_p;
		++ssvstr_p;
	}
finish:
	
	return str;
}
