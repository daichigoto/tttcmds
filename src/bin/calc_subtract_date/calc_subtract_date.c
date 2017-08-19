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
	getcmdargs(argc, argv, "f:shvD", 
	           CMDARGS_R_NONE|CMDARGS_A_NEED|CMDARGS_F_NONE);

	if (2 != A_ARGC)
		usage();

	const char *in_fmt = "%Y%m%d";
	if (FLAG_f)
		in_fmt = FLAG_f_ARG;

	const char *date_B = A_ARGV[1];
	const char *date_A = A_ARGV[2];

	time_t tval_A, tval_B;
	struct tm lt_A, lt_B;
	const char *t;

	(void)setlocale(LC_TIME, "");
	time(&tval_A);
	lt_A = *localtime(&tval_A);
	tval_B = tval_A;
	lt_B = lt_A;

	t = strptime(date_A, in_fmt, &lt_A);
	check_t(t, date_A, in_fmt);
	tval_A = mktime(&lt_A);

	t = strptime(date_B, in_fmt, &lt_B);
	check_t(t, date_B, in_fmt);
	tval_B = mktime(&lt_B);

	long sec = tval_A - tval_B;

	if (FLAG_s)
		/* output in seconds */
		printf("%ld\n", sec);
	else
		/* output in days */
		printf("%ld\n", sec / 60 / 60 / 24);

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
