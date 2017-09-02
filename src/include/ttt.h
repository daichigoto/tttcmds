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

#ifndef _TTT_H_
#define _TTT_H_

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <err.h>

#define BUFFER_SIZE 			4096
#define STDIN_FILE			"/dev/stdin"

#define CMDARGS_DEFAULT			0x00000000
#define CMDARGS_R_NONE			0x00000001
#define CMDARGS_R_NEED			0x00000002
#define CMDARGS_R_ARGARG_NONE		0x00000004
#define CMDARGS_R_ARGARG_1_NEED		0x00000008
#define CMDARGS_R_ARGARG_2_NEED		0x00000010
#define CMDARGS_R_ARGARG_3_NEED		0x00000020
#define CMDARGS_R_ARGARG_TO_SSVSTR	0x00000040
#define CMDARGS_F_NONE			0x00000100
#define CMDARGS_F_NEED			0x00000200
#define CMDARGS_STDIN_TO_TMPFILE	0x00000400
#define CMDARGS_A_NONE			0x00001000
#define CMDARGS_A_NEED			0x00002000
#define CMDARGS_R_MINIMUMNUM_IS_0	0x00010000
#define CMDARGS_R_MINIMUMNUM_IS_1	0x00020000

struct tttcmdargs {
	char	*cmdname;
	int	flags[63];
	char	*flags_arg[63];
	int 	r_argc;
	int	r_argv_max;
	int	*r_argv;
	int	r_index_max;
	int	*r_index_exist;
	int	*r_index_to_argv;
	char	**r_argv_arg1;
	char	**r_argv_arg2;
	char	**r_argv_arg3;
	char	*r_argv_delim;
	int	f_argc;
	char	**f_argv;
	int	a_argc;
	char	**a_argv;
};

extern struct tttcmdargs cmdargs;

#define TEXTSET_END			{ NULL, NULL, NULL }

struct textset {
	char	*key;
	char	*locale;
	char	*text;
};

extern struct textset deftextsets[];
extern struct textset cmdtextsets[] __attribute__((__weak__));
extern struct textset *textsets[];

struct ssvline {
	char		**data;
	int		nf;
	struct ssvline	*next;
	int		outputed;
};

int getcmdargs(const int, char *[], const char *, int);
int getcmdargs_unlinktmpf(void);
char *gettext(const char *);
int settext(const char *, const char *, const char *);
int settime(struct tm *, const char *, const char *);
void ssvfile2ssvlines(const char *, struct ssvline *);
char *ssvstr2str(char *, char *);
int ssvstr2str_len(char *);
char *str2ssvstr(char *, char *);
int str2ssvstr_len(char *);
int gettimestr(char [], const char *, struct tm *);
void usage(void);
void printcmdargs(void);
void version(void);

char *_str2ssvstr(char *);
char *_ssvstr2str(char *);
char *_ltgt2charref(char *);
char *_quote2charref(char *);

#include "ttt_aliases.h"
#include "ttt_text.h"
#include "ttt_utils.h"
#include "ttt_debug.h"

#ifdef __linux__
#include <bsd/stdlib.h>
#endif

#endif /* !_TTT_H_ */
