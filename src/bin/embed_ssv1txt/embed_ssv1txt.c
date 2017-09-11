/*
 * Copyright (c) 2016,2017 Daichi GOTO
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
	getcmdargs(argc, argv, "bt:s:m:nhvD", CMDARGS_DEFAULT);

	struct stat sb;
	int tsize = 0, fd, rs = 0, len = 0, max, m, match;
	char *tbuf, *bbuf, *bbuf_p1, *bbuf_p2;

	/*
	 * required option
	 */
	if (!FLAG_t)
		usage();
	if (!FLAG_s && 0 == R_ARGC)
		usage();
	if (-1 == stat(FLAG_t_ARG, &sb))
		err(errno, "%s", FLAG_t_ARG);
	if (FLAG_s && -1 == stat(FLAG_s_ARG, &sb))
		err(errno, "%s", FLAG_s_ARG);

	/*
	 * swap rule setup
	 */
	if (FLAG_s) {
		FILE *fp;
		if (NULL == (fp = fopen(FLAG_s_ARG, "r")))
			err(errno, "%s", FLAG_s_ARG);

		char buf[BUFSIZ], *p, *p2;
		int gyo = 0, n;
		struct swaprules *s, *s_s;
		s = calloc(1, sizeof(struct swaprules));
		s_s = s;

		while (NULL != fgets(buf, BUFSIZ, fp)) {
			if (2 <= strlen(buf)) {
				p = buf;
				while (isdigit(*p))
					++p;
				*p = '\0';
				errno = 0;
				n = (int)strtol(buf, (char **)NULL, 10);
				if (EINVAL == errno)
					err(errno, "%s", buf);
				++p;
				p2 = p;
				while ('\n' != *p && '\0' != *p)
					++p;
				*p = '\0';
				s->r = n;
				s->r_arg = calloc(1, 
					(strlen(p2) + 1) * sizeof(char));
				strcpy(s->r_arg, p2);
				s->next = calloc(1, 
					sizeof(struct swaprules));
				s = s->next;
				++gyo;
			}
		}
		fclose(fp);

		R_ARGC = gyo;
		R_ARGV = calloc(1, (1 + gyo) * sizeof(int));
		R_ARGV_ARG1 = calloc(1, (1 + gyo) * sizeof(char *));
		R_ARGV[0] = -1;
		s = s_s;
		for (int i = 1; i <= R_ARGC; i++) {
			R_ARGV[i] = s->r;
			R_ARGV_ARG1[i] = s->r_arg;
			if (s->r > R_ARGV_MAX)
				R_ARGV_MAX = s->r;
			s = s->next;
		}
	}

	if (FLAG_D)
		printcmdargs();

	/*
	 * template text file into the template buffer
	 */
	stat(FLAG_t_ARG, &sb);
	tsize = sb.st_size;
	tbuf = calloc(1, (tsize + 1) * sizeof(char));
	
	if (-1 == (fd = open(FLAG_t_ARG, O_RDONLY)))
		err(errno, "%s", FLAG_t_ARG);
	while (rs != tsize)
		rs += read(fd, tbuf + rs, tsize - rs);
	tbuf[tsize] = '\0';
	close(fd);

	/*
	 * FLAG_n process
	 */
	if (FLAG_n && '\n' == tbuf[tsize - 1])
		tbuf[tsize - 1] = '\0';

	/*
	 * FLAG_m process
	 */
	if (FLAG_m) {
		errno = 0;
		max = (int)strtol(FLAG_m_ARG, (char **)NULL, 10);
		if (EINVAL == errno)
			err(errno, "%s", FLAG_m_ARG);
	}

	FILEPROCESS_GYO

	exit(EX_OK);
}
