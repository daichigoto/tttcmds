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

#define	LINE_BUF_MAX	3145728

#define	IS_NUM(p) 					\
	(48 <= *p && *p <= 57)

#define	IS_SEPARATOR(p)					\
	' ' == *p || '\n' == *p || '\0' == *p
#define	IS_NOT_SEPARATOR(p)				\
	' ' != *p && '\n' != *p && '\0' != *p

#define	IS_SPACE(p)					\
	' ' == *p 

enum COMPARISON_TYPE {
	EQUAL_TO,
	NOT_EQUAL_TO,
	GREATER_THAN,
	LESS_THAN,
	GREATER_THAN_OR_EQUAL_TO,
	LESS_THAN_OR_EQUAL_TO
};

static void process_equal_to(char *, char *, int);
static void process_equal_to_empty(char *, char *, int);
static void process_not_equal_to(char *, char *, int);
static void process_not_equal_to_empty(char *, char *, int);
static void process_greater_than(char *, char *, int);
static void process_less_than(char *, char *, int);
static void process_greater_than_or_equal_to(char *, char *, int);
static void process_less_than_or_equal_to(char *, char *, int);

void
simple_comparison()
{
	// Only one column can be processed with option -s
	if (1 != R_ARGC) {
		warn("Only one column can be processed with option -s");
		usage();
	}

	// Condition determination
	char *target_argv = R_ARGV_ARG1[1];
	char delim = R_ARGV_DELIM[1];

	enum COMPARISON_TYPE comp_type;
	if ('!' == delim) {
		comp_type = NOT_EQUAL_TO;
	}
	else if ('=' == delim && '>' == *target_argv) {
		comp_type = GREATER_THAN_OR_EQUAL_TO;
		++target_argv;
	}
	else if ('>' == delim && '=' == *target_argv) {
		comp_type = GREATER_THAN_OR_EQUAL_TO;
		++target_argv;
	}
	else if ('>' == delim) {
		comp_type = GREATER_THAN;
	}
	else if ('=' == delim && '<' == *target_argv) {
		comp_type = LESS_THAN_OR_EQUAL_TO;
		++target_argv;
	}
	else if ('<' == delim && '=' == *target_argv) {
		comp_type = LESS_THAN_OR_EQUAL_TO;
		++target_argv;
	}
	else if ('<' == delim) {
		comp_type = LESS_THAN;
	}
	else {
		comp_type = EQUAL_TO;
	}

	// Keyword extraction
	char *keyword = target_argv;

	// Target row number
	int target_retu = R_ARGV[1];

	// Compare and output
	for (int file_i = 1; file_i <= F_ARGC; file_i++) {
		// If the keyword is @, both @ and "" need to be compared.
		// In addition, inequality cannot be processed. So separate
		// processing for higher speed.
		if (0 == strcmp(keyword, "@")) {
			switch (comp_type) {
			case EQUAL_TO:
				process_equal_to_empty
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			case NOT_EQUAL_TO:
				process_not_equal_to_empty
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			case GREATER_THAN:
				// Inequality cannot be processed
				break;
			case LESS_THAN:
				// Inequality cannot be processed
				break;
			case GREATER_THAN_OR_EQUAL_TO:
				// Inequality cannot be processed.
				// Perform only equivalent processing.
				process_equal_to_empty
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			case LESS_THAN_OR_EQUAL_TO:
				// Inequality cannot be processed.
				// Perform only equivalent processing.
				process_equal_to_empty
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			}
		}
		else {
			switch (comp_type) {
			case EQUAL_TO:
				process_equal_to
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			case NOT_EQUAL_TO:
				process_not_equal_to
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			case GREATER_THAN:
				process_greater_than
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			case LESS_THAN:
				process_less_than
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			case GREATER_THAN_OR_EQUAL_TO:
				process_greater_than_or_equal_to
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			case LESS_THAN_OR_EQUAL_TO:
				process_less_than_or_equal_to
					(F_ARGV[file_i], keyword, 
					 target_retu);
				break;
			}
		}
	}
}

#define	PROCESS_PRE_TREATMENT					\
	FILE *fp;						\
								\
	/*							\
	 * MSYS2 (Cygwin) stack memory is limited to a few MB	\
	 * and crashes quickly. To avoid consuming the stack	\
	 * memory, large buffers should be allocated in the	\
	 * heap memory.						\
	 */							\
	char *line_buf;						\
        line_buf = calloc(LINE_BUF_MAX, sizeof(char *));	\
	char *p;						\
								\
	int keyword_len = strlen(keyword);			\
	bool not_enough_columns;				\
								\
	FILEPROCESS_FOPEN(fp, fpath, "r")			\
								\
	while (NULL != fgets(line_buf, LINE_BUF_MAX, fp)) {	\
		/* Seek to the target row */			\
		p = line_buf;					\
		not_enough_columns = false;			\
		for (int i = 1; i < target_retu; i++) {		\
			while (IS_NOT_SEPARATOR(p))		\
				++p;				\
			if (IS_SPACE(p))			\
				++p;				\
			else {					\
				not_enough_columns = true;	\
				break;				\
			}					\
		}						\
								\
		if (not_enough_columns) {			\
			printf("%s", line_buf);			\
			continue;				\
		}

#define PROCESS_POST_TREATMENT					\
	}							\
	fclose(fp);

static void
process_equal_to
	(char *fpath, char *keyword, int target_retu)
{
	PROCESS_PRE_TREATMENT

	// Compare and output
	if (0 == strncmp(p, keyword, keyword_len))
		;
	else
		printf("%s", line_buf);

	PROCESS_POST_TREATMENT
}

static void
process_equal_to_empty
	(char *fpath, char *keyword, int target_retu)
{
	PROCESS_PRE_TREATMENT

	// Compare and output
	if (0 == strncmp(p, keyword, keyword_len))
		;
	else if (IS_SEPARATOR(p))
		;
	else
		printf("%s", line_buf);

	PROCESS_POST_TREATMENT
}

static void
process_not_equal_to
	(char *fpath, char *keyword, int target_retu)
{
	PROCESS_PRE_TREATMENT

	// Compare and output
	if (0 != strncmp(p, keyword, keyword_len))
		;
	else
		printf("%s", line_buf);

	PROCESS_POST_TREATMENT
}

static void
process_not_equal_to_empty
	(char *fpath, char *keyword, int target_retu)
{
	PROCESS_PRE_TREATMENT

	// Compare and output
	if (0 != strncmp(p, keyword, keyword_len) &&
	    IS_NOT_SEPARATOR(p))
		;
	else
		printf("%s", line_buf);

	PROCESS_POST_TREATMENT
}

static void
process_greater_than
	(char *fpath, char *keyword, int target_retu)
{
	PROCESS_PRE_TREATMENT

	// Compare and output
	if (0 < strncmp(p, keyword, keyword_len))
		;
	else
		printf("%s", line_buf);

	PROCESS_POST_TREATMENT
}

static void
process_less_than
	(char *fpath, char *keyword, int target_retu)
{
	PROCESS_PRE_TREATMENT

	// Compare and output
	if (0 > strncmp(p, keyword, keyword_len))
		;
	else
		printf("%s", line_buf);

	PROCESS_POST_TREATMENT
}

static void
process_greater_than_or_equal_to
	(char *fpath, char *keyword, int target_retu)
{
	PROCESS_PRE_TREATMENT

	// Compare and output
	if (0 <= strncmp(p, keyword, keyword_len))
		;
	else
		printf("%s", line_buf);

	PROCESS_POST_TREATMENT
}

static void
process_less_than_or_equal_to
	(char *fpath, char *keyword, int target_retu)
{
	PROCESS_PRE_TREATMENT

	// Compare and output
	if (0 >= strncmp(p, keyword, keyword_len))
		;
	else
		printf("%s", line_buf);

	PROCESS_POST_TREATMENT
}
