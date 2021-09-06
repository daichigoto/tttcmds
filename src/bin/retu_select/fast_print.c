/*
 * Copyright (c) 2019,2021 Daichi GOTO
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

#define LINE_BUF_MAX	3145728

#define	IS_SEPARATOR(p)					\
	' ' == *p || '\n' == *p || '\0' == *p
#define	IS_NOT_SEPARATOR(p)				\
	' ' != *p && '\n' != *p && '\0' != *p

#define	IS_SPACE(p)					\
	' ' == *p 

#define	IS_LF(p)					\
	'\n' == *p 

static const char atmark[2] = "@";

static inline void do_fast_print(FILE *fp);

static bool outputed;

void
fast_print(void)
{
	FILE *fp;

	outputed = false;

	// Process the first file
	int file_i = 1;

	// MSYS2 (Cygwin) stack memory is limited to a few MB and crashes 
	// quickly. To avoid consuming the stack memory, large buffers 
	// should be allocated in the heap memory.
	char *line_buf;
	line_buf = calloc(LINE_BUF_MAX, sizeof(char *));

	fp = fopen(F_ARGV[file_i], "r");
	if (NULL == fp)
		err(errno, "%s", F_ARGV[file_i]);

	// Delete the first line
	if (FLAG_1)
		fgets(line_buf, LINE_BUF_MAX, fp);

	do_fast_print(fp);

	fclose(fp);

	// Process second and subsequent files
	for (file_i = 2; file_i <= F_ARGC; file_i++) {
		fp = fopen(F_ARGV[file_i], "r");
		if (NULL == fp)
			err(errno, "%s", F_ARGV[file_i]);

		do_fast_print(fp);

		fclose(fp);
	}

	// If option -e is specified, only one line is output if 
	// there is no output.
	if (FLAG_e && ! outputed) {
		for (int i = 1; i < R_ARGC; i++)
			printf("@ ");
		printf("@\n");
	}
}

static inline void
do_fast_print(FILE *fp)
{
	// MSYS2 (Cygwin) stack memory is limited to a few MB and crashes 
	// quickly. To avoid consuming the stack memory, large buffers 
	// should be allocated in the heap memory.
	char *line_buf;
	line_buf = calloc(LINE_BUF_MAX, sizeof(char *));

	char *p;
	char *retu_p;

	// Array to access the string of columns from the number of 
	// columns:
	// 	retu_to_string[RETU_NUMBER] --> RETU_STRING 
	//
	char *retu_to_string[1 + R_INDEX_MAX];

	// 0 is always access to the atmark.
	retu_to_string[0] = atmark;

	while (NULL != fgets(line_buf, LINE_BUF_MAX, fp)) {
		// Divide the line_buf by column and set access method 
		// (retu_to_string[RETU_NUMBER] --> RETU_STRING).
		p = line_buf;

		for (int retu_i = 1; retu_i <= R_INDEX_MAX; 
			retu_i++) {

			// Pointer to the column string
			retu_p = p;

			// Move to end of string
			while (IS_NOT_SEPARATOR(p))
				++p;

			// Set access if selected column
			if (R_INDEX_EXIST[retu_i]) {
				if (retu_p == p)
					retu_to_string[retu_i] = atmark;
				else
					retu_to_string[retu_i] = retu_p;
			}

			// Move to beginning of next column
			if (IS_SPACE(p)) {
				*p = '\0';
				++p;
			}
			// Since there is no line data left, everything 
			// is set to access "@"
			else {
				if (IS_LF(p))
					*p = '\0';

				for (++retu_i; retu_i <= R_INDEX_MAX; 
					retu_i++) {
					if (R_INDEX_EXIST[retu_i])
						retu_to_string[retu_i] = 
							atmark;
				}
			}
		}

		// Output in specified column order
		for (int retu_i = 1; retu_i < R_ARGC; retu_i++)
			printf("%s ", retu_to_string[R_ARGV[retu_i]]);
		printf("%s\n", retu_to_string[R_ARGV[R_ARGC]]);

		outputed = true;
	}
}
