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

struct ssvline {
	char		**data;
	int		nf;
	struct ssvline	*next;
};

static void ssv2ssvlines(char *);
static struct ssvline ssv_firstline;

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "rhvD",
	           CMDARGS_R_NEED|
		   CMDARGS_F_NEED|
		   CMDARGS_STDIN_TO_TMPFILE);

	int rightkeys[R_ARGC+1], rightoutnum = 0, rightnf;
	int match, match1, match2, spaces;
	for (int i = 1; i <= R_ARGC; i++) {
		errno = 0;
		rightkeys[i] =
			(int)strtol(R_ARGV_ARG1[i], (char **)NULL, 10);
		match = 0;
		for (int j = 1; j < i; j++)
			if (rightkeys[j] == rightkeys[i])
				match = 1;
		if (!match)
			++rightoutnum;
		if (EINVAL == errno)
			usage();
	}

	if (2 != F_ARGC)
		usage();

	ssv2ssvlines(F_ARGV[2]);
	F_ARGC = 1;

	struct ssvline *p_ssvline;
	FILEPROCESS_GYO

	exit(EX_OK);
}

void
ssv2ssvlines(char *filename)
{
	struct ssvline *p_ssvline;
	FILE *fp;
	const int buflen = 4096;
	int len;
	char buf[buflen], *p;

	fp = fopen(filename, "r");
	if (NULL == fp)
		err(errno, "%s", filename);

	p_ssvline = &ssv_firstline;
	p_ssvline->data = NULL;
	p_ssvline->next = NULL;
	p_ssvline->nf = 0;
	while (NULL != fgets(buf, buflen, fp)) {
		/*
		 * Next ssvline
		 */
		if (NULL != p_ssvline->data) {
			p_ssvline->next = 
				calloc(1, sizeof(struct ssvline));
			p_ssvline = p_ssvline->next;
		}

		/*
		 * Check NF
		 */
		p = buf;
		p_ssvline->nf = 0;
		while ('\0' != *p) {
			if (' ' == *p) {
				++(p_ssvline->nf);
				*p = '\0';
			}
			else if ('\n' == *p)
				*p = '\0';
			++p;
		}
		++(p_ssvline->nf);

		/*
		 * Copy data
		 */
		p = buf;
		p_ssvline->data = 
			calloc(1, sizeof(char *) * (p_ssvline->nf + 1));
		for (int i = 1; i <= p_ssvline->nf; i++) {
			len = strlen(p);
			p_ssvline->data[i] =
				calloc(1, sizeof(char) * (len + 1));
			strcpy(p_ssvline->data[i], p);
			while ('\0' != *p)
				++p;
			++p;
		}
	}
	fclose(fp);

	if (FLAG_D) {
		p_ssvline = &ssv_firstline;
		do {
			for (int i = 1; i < p_ssvline->nf; i++) {
				printf("%s ", p_ssvline->data[i]);
			}
			if (0 != p_ssvline->nf) {
				printf("%s\n", 
					p_ssvline->data[p_ssvline->nf]);
				p_ssvline = p_ssvline->next;
			}
			else
				break;
		}
		while (NULL != p_ssvline);
	}
}
