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

static void check_t(const char *, const char *, const char *);

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "c:i:o:V:hvD", CMDARGS_R_NONE);

	/*
	 * with    -c: first date is required.
	 * without -c: first date and last date are required.
	 */
	const char *first, *last;
	if ((!FLAG_c && 2 != F_ARGC) || (FLAG_c && 1 != F_ARGC))
		usage();
	if (FLAG_c)
		first = F_ARGV[1];
	else {
		first = F_ARGV[1];
		last = F_ARGV[2];
	}

	/*
	 * set options
	 */
	const char *in_fmt = "%Y%m%d";
	const char *out_fmt = "%Y%m%d";
	const char *val = "+1d";
	int count = 0;
	if (FLAG_i)
		in_fmt = FLAG_i_ARG;
	if (FLAG_o)
		out_fmt = FLAG_o_ARG;
	if (FLAG_V)
		val = FLAG_V_ARG;
	if (FLAG_c) {
		errno = 0;
		count = (int)strtol(FLAG_c_ARG, (char **)NULL, 10);
		if (EINVAL == errno)
			usage();
	}

	/*
	 * set up the first date and the last date
	 */
	time_t tval, tval_last;
	struct tm lt, lt_last;
	const char *t;

	(void)setlocale(LC_TIME, "");
	time(&tval);
	tval_last = tval;
	lt = *localtime(&tval);
	lt_last = lt;

	t = strptime(first, in_fmt, &lt);
	check_t(t, first, in_fmt);
	tval = mktime(&lt);

	if (!FLAG_c) {
		t = strptime(last, in_fmt, &lt_last);
		check_t(t, last, in_fmt);
		tval_last = mktime(&lt_last);
	}

	/*
	 * set up the increments or the decrements
	 */
	struct vary *v = NULL;
	v = vary_append(v, val);

	/*
	 * print a sequence of dates
	 */
	char buf[1024];

	for (int i = 1; ; i++) {
		if (FLAG_c) {
			if (i > count)
				break;
		}
		else {
			if ('+' == val[0]) {
				if (tval > tval_last)
					break;
			}
			else if ('-' == val[0]) {
				if (tval < tval_last)
					break;
			}
			else
				usage();
		}

		(void)strftime(buf, sizeof(buf), out_fmt, &lt);
		(void)printf("%s\n", buf);
		
		vary_apply(v, &lt);
		tval = mktime(&lt);
	}

	exit(EX_OK);
}

static void
check_t(const char *t, const char *date, const char *fmt)
{
/*
 * Copied from date.c of FreeBSD 11.0-RELEASE and modified.
 */
	if (t == NULL) {
		fprintf(stderr, "Failed conversion of ``%s''"
			" using format ``%s''\n", date, fmt);
		warnx("illegal time format");
		usage();
	}
	else if ('\0' != *t)
		fprintf(stderr, "Warning: Ignoring %ld extraneous"
			" characters in date string (%s)\n",
			(long) strlen(t), t);
/*-
 * Copyright (c) 1985, 1987, 1988, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
}
