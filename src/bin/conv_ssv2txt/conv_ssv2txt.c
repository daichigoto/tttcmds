/*
 * Copyright (c) 2016,2017,2019,2021,2023 Daichi GOTO
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

#include "command.h"

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "thvD",
	           CMDARGS_R_NONE|CMDARGS_STDIN_TO_TMPFILE);

	if (FLAG_t) {
		/*
		 * count the max number of columns
		 */
		int retu = -1, i = 0;
		char p = EOF;
		FILEPROCESS_CHAR
		if (0 == retu)
			exit(EX_OK);
	
		/*
		 * count the max length for each column
		 */
		int maxlen[retu + 1], len;
		memset(maxlen, 0, sizeof(int) * (retu + 1));
		FILEPROCESS_GYO
	
		/*
		 * convert the ssv data to the text table data
		 */
		int count;
		char *buf[retu + 1];
		for (i = 1; i <= retu; i++)
			buf[i] = calloc(maxlen[i] + 1, sizeof(char));
		FILEPROCESS_RETU
	}
	else {
		/*
		 * convert the ssv data to the text data
		 */
		FILEPROCESS_ALLBUFFER
	}

	getcmdargs_unlinktmpf();

	exit(EX_OK);
}

/*
 * Returns the width (number of half-width characters) in the terminal.
 */
int
width_in_terminal(const char *buf)
{
	const char *p;
	p = buf;

	// Store the width of the string in the terminal (counted by the number 
	// of half-width characters).
	int width_in_terminal = 0;

	// Applies the current locale, required for mblen() to work properly.
	setlocale(LC_CTYPE, "");

	while('\0' != *p){
		int char_bytes = mblen(p, MB_CUR_MAX);

		// Determine the width of the characters and add them up.
		// (Simple implementation. To make it accurate, it is necessary to 
		//  perform the judgment process strictly for each encoding.)
		if (1 == char_bytes) {

			// 1 byte is assumed to be a half-width character.
			width_in_terminal += 1;
		}
		else {
			// 2 or more bytes are assumed to be a full-width character.
			width_in_terminal += 2;
		}

		p += char_bytes;
	}

	return width_in_terminal;
}
