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
str2ssvstr(char *ssvstr, char *str)
{
	char *str_p, *ssvstr_p;
	str_p = str;
	ssvstr_p = ssvstr;

	if (NULL == str) {
		*ssvstr_p = '\0';
		return ssvstr;
	}
	if ('\0' == *str_p) {
		*ssvstr_p = '@';
		*(ssvstr_p + 1) = '\0';
		return ssvstr;
	}

	while (1) {
		switch (*str_p) {
		case ' ':
			*ssvstr_p = '_';
			break;
		case '@':
		case '_':
			*ssvstr_p = '\\';
			++ssvstr_p;
			*ssvstr_p = *str_p;
			break;
		case '\0':
			*ssvstr_p = '\0';
			goto finish;
		default:
			*ssvstr_p = *str_p;
			break;
		}
		++str_p;
		++ssvstr_p;
	}
finish:
	
	return ssvstr;
}
