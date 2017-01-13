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

#include "ttt.h"

char *
_quote2charref(char *str)
{
	char *buf, *p;
	int len, i;
	for (p = str, len = 0; *p != '\0'; p++)
		if ('"' == *p)
			len += 6; /* &quot; */
		else if ('\'' == *p)
			len += 5; /* &#39; */
		else
			++len;
	buf = calloc(1, sizeof(char) * (len + 1));
	buf[len] = '\0';

	for (i = 0, p = str; i < len; p++, i++)
		if ('"' == *p) {
			buf[i++] = '&';
			buf[i++] = 'q';
			buf[i++] = 'u';
			buf[i++] = 'o';
			buf[i++] = 't';
			buf[i] = ';';
		}
		else if ('\'' == *p) {
			buf[i++] = '&';
			buf[i++] = '#';
			buf[i++] = '3';
			buf[i++] = '9';
			buf[i] = ';';
		}
		else
			buf[i] = *p;
	
	return buf;
}
