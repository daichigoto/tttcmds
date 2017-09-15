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

#include "command.h"

static void to_intarray(char *, int *, int *);

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "d:rhvD",
	           CMDARGS_R_NEED|CMDARGS_R_ARGARG_1_NEED);

	char *delim = "";
	int delim_len = 0;
	if (FLAG_d) {
		delim = _str2ssvstr(FLAG_d_ARG);
		delim_len = strlen(delim);
	}

	/*
	 * target cols to int array - appcols[][], appcols_len[]
	 */
	int **appcols, appcols_len[R_ARGC+1];
	appcols = (int **)calloc(R_ARGC+1, sizeof(int *));
	for (int i = 0; i <= R_ARGC; i++) 
		appcols[i] = (int *)calloc(4096, sizeof(int));

	for (int i = 1; i <= R_ARGC; i++) {
		to_intarray(R_ARGV_ARG1[i], appcols[i], &appcols_len[i]);
	}

	/*
	 * remove target cols - remcols[], remcols_max, remcols_num;
	 */
	int remcols_max = 0;
	for (int i = 1; i <= R_ARGC; i++) {
		for (int j = 1; j <= appcols_len[i]; j++) {
			if (remcols_max < appcols[i][j])
				remcols_max = appcols[i][j];
		}
	}
	int remcols[remcols_max+1];
	for (int i = 0; i <= remcols_max; i++)
		remcols[i] = 0;
	for (int i = 1; i <= R_ARGC; i++) {
		for (int j = 1; j <= appcols_len[i]; j++) {
			remcols[appcols[i][j]] = 1;
		}
	}
	int remcols_num = 0;
	for (int i = 1; i <= remcols_max; i++)
		if (1 == remcols[i])
			++remcols_num;

	if (FLAG_D) {
		fprintf(stderr, "remcols: ");
		for (int i = 0; i <= remcols_max; i++)
			fprintf(stderr, "%d ", remcols[i]);
		fprintf(stderr, "\n");
		fprintf(stderr, "remcols_max: %d\n", remcols_max);
		fprintf(stderr, "remcols_num: %d\n", remcols_num);
		
		for (int i = 1; i <= R_ARGC; i++) {
			fprintf(stderr, "appcols[%d][] --> ", i);
			for (int j = 1; j <= appcols_len[i]; j++) 
				fprintf(stderr, "%d ", appcols[i][j]);
			fprintf(stderr, "\n");
		}
	}

	char *buf[R_ARGC+1], *buf_p;
	int len, spaces;
	FILEPROCESS_GYO

	exit(EX_OK);
}

static void
to_intarray(char *cols, int *i_a, int *i_a_len)
{
	char *p;
	int slash = 0, delim = 0;

	/*
	 * columns check
	 */
	p = cols;
	while (*p != '\0') {
		if ('/' == *p) {
			++slash;
		}
		else if ((int)*p < 48 || 57 < (int)*p) {
			++delim;
		}
		++p;
	}

	/*
	 * a column
	 */
	if (0 == slash && 0 == delim) {
		p = cols;
		int col = 0;
		while (*p != '\0') {
			col = 10 * col + (int)(*p) - 48;
			++p;
		}
		i_a[1] = col;
		*i_a_len = 1;
	}
	/*
	 * multi coulumns
	 */
	else if (0 == slash && 0 != delim) {
		p = cols;
		int col = 0, i = 1, len = 0;
		while (1) {
			if ((int)*p < 48 || 57 < (int)*p) {
				if (0 == col)
					usage();
				i_a[i] = col;
				if (*p == '\0') {
					++len;
					*i_a_len = len;
					break;
				}
				col = 0;
				++i;
				++len;
			}
			else {
				col = 10 * col + (int)(*p) - 48;
			}
			++p;
		}
	}
	/*
	 * multi coulumns by slash range
	 */
	else if (1 == slash) {
		p = cols;
		int start, end;
		start = end = 0;
		while (*p != '/') {
			NUM_CHECK(*p)
			start = 10 * start + (int)(*p) - 48;
			++p;
		}
		++p;
		while (*p != '\0') {
			NUM_CHECK(*p)
			end = 10 * end + (int)(*p) - 48;
			++p;
		}
		for (int i = 1, j = start; j <= end; i++, j++)
			i_a[i] = j;
		*i_a_len = end - start + 1;
	}
	else
		usage();
}
