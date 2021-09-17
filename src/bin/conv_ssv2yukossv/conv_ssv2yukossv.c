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

#define	IS_NOT_SEPARATOR(p)			\
	' ' != *p && '\n' != *p && '\0' != *p
/*
 * UTF-8:
 * 	有効 == 0xe6 0x9c 0x89 0xe5 0x8a 0xb9
 * 	無効 == 0xe7 0x84 0xa1 0xe5 0x8a 0xb9
 * 	NUL  == 0x00
 * 	LF   == 0x0a
 *	SP   == 0x20
 */
#define	IS_YUKO(p)				\
	if ((char)0xe6 == *p && 		\
	    (char)0x9c == *(p + 1) && 		\
	    (char)0x89 == *(p + 2) &&		\
	    (char)0xe5 == *(p + 3) &&		\
	    (char)0x8a == *(p + 4) &&		\
	    (char)0xb9 == *(p + 5) &&		\
	    ((char)0x20 == *(p + 6) || 		\
	     (char)0x0a == *(p + 6) || 		\
	     (char)0x00 == *(p + 6))		\
		) 

static inline void print_line(char *, int);
static inline void print_dbt(DBT *);
static inline void println_dbt(DBT *);

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "dhvD", CMDARGS_R_NONE);

	DB	*btree;
	DBT	key, val;

	FILE	*fp;

	// MSYS2 (Cygwin) stack memory is limited to a few MB and crashes 
	// quickly. To avoid consuming the stack memory, large buffers 
	// should be allocated in the heap memory.
	char	*line_buf;
	line_buf = calloc(LINE_BUF_MAX, sizeof(char *));

	int	line_len;
	int	id_len;

	// Create btree storage
	btree = dbopen(NULL, O_CREAT | O_RDWR, 0666, DB_BTREE, NULL);

	FILEPROCESS_FOPEN(fp, F_ARGV[1], "r")

	while (NULL != fgets(line_buf, LINE_BUF_MAX, fp)) {
		// Remove the line feed from the line
		char *p_to_linefeed;
		line_len = strlen(line_buf);
		p_to_linefeed = line_buf + line_len - 1;
		if ('\n' == *p_to_linefeed)
			*p_to_linefeed = '\0';
		else
			++line_len;

		// The 1st and 2nd columns is a btree's ID.
		char *p;
		p = line_buf;
		id_len = 0;
		while (IS_NOT_SEPARATOR(p)) {
			++id_len;
			++p;
		}
		if (' ' == *p) {
			++id_len;
			++p;
		}
		while (IS_NOT_SEPARATOR(p)) {
			++id_len;
			++p;
		}

		// Store the row in btree with ID as an uniq key.
		// The same ID's data will be overwritten.
		key.data = line_buf;
		key.size = id_len;
		val.data = line_buf;
		val.size = line_len;

		btree->put(btree, &key, &val, 0);
	}
	fclose(fp);

	/*
	 * For each ID, output the most recent and valid data.
	 * The valid in this case means that the value in the fourth 
	 * column is "有効" in UTF-8.
	 * 	UTF-8:
	 * 		有効 == 0xe6 0x9c 0x89 0xe5 0x8a 0xb9 
	 * 		無効 == 0xe7 0x84 0xa1 0xe5 0x8a 0xb9 
	 */
// MSYS2, Linux - Normal Code
#if defined(__MSYS__) || defined(__linux__)
	bool first_line = true;
	int previous_1st_colm_len;
	char previous_1st_colm[4096];

	// MSYS2 (Cygwin) stack memory is limited to a few MB and crashes 
	// quickly. To avoid consuming the stack memory, large buffers 
	// should be allocated in the heap memory.
	char *previous_line;
	previous_line = calloc(LINE_BUF_MAX, sizeof(char *));

	char *p = NULL;

	while (0 == btree->seq(btree, &key, &val, R_NEXT)) {
		// BEGIN
		if (first_line) {
			p = key.data;
			previous_1st_colm_len = 0;
			while (IS_NOT_SEPARATOR(p)) {
				++previous_1st_colm_len;
				++p;
			}
			memcpy(previous_1st_colm, key.data, previous_1st_colm_len);
			memcpy(previous_line, val.data, val.size);

			first_line = false;
			continue;
		}
		// ID is the same as previous line
		else if (0 == strncmp(previous_1st_colm, key.data, previous_1st_colm_len)) {
			memcpy(previous_line, val.data, val.size);
			continue;
		}
		// ID is different from the previous line.
		// Check the 4th column and print if valid.
		else {
			print_line(previous_line, FLAG_d);

			p = key.data;
			previous_1st_colm_len = 0;
			while (IS_NOT_SEPARATOR(p)) {
				++previous_1st_colm_len;
				++p;
			}
			memcpy(previous_1st_colm, key.data, previous_1st_colm_len);
			memcpy(previous_line, val.data, val.size);
		}
	}
	// END
	print_line(previous_line, FLAG_d);
#else
// FreeBSD, Mac - High Speed Processing Code
	char *previous_line;
	int key_len;

	key_len = 0;
	previous_line = NULL;
	while (0 == btree->seq(btree, &key, &val, R_NEXT)) {
		char *p;
		p = val.data;

		// BEGIN
		if (NULL == previous_line) {
			previous_line = val.data;
			while (IS_NOT_SEPARATOR(p)) {
				++p;
			}
			key_len = p - previous_line;
			continue;
		}
		// ID is the same as previous line	
		else if (0 == strncmp(previous_line, val.data, key_len)) {
			previous_line = val.data;
			continue;
		}
		// ID is different from the previous line.
		// Check the 4th column and print if valid.
		else {
			print_line(previous_line, FLAG_d);
			previous_line = val.data;
		}
	}
	// END
	print_line(previous_line, FLAG_d);
#endif

	exit(EX_OK);
}

static inline void
print_line(char *line, int delete_flag)
{
	if (NULL == line)
		return;

	char *p;
	p = line;

	// Move the pointer to the fourth row
	while (IS_NOT_SEPARATOR(p))
		++p;
	if (' ' == *p) 
		++p;
	while (IS_NOT_SEPARATOR(p))
		++p;
	if (' ' == *p) 
		++p;
	while (IS_NOT_SEPARATOR(p))
		++p;

	// Do not output because of inappropriate format
	if (' ' != *p) 
		return;

	++p;
	IS_YUKO(p) {
		p = line;
		if (delete_flag) {
			// Output the first column
			while (' ' != *p) {
				putchar(*p);
				++p;
			}
			// Skip the send column
			++p;
			while (' ' != *p)
				++p;
			// Skip the third column
			++p;
			while (' ' != *p)
				++p;
			// Skip the fourth column
			++p;
			while (IS_NOT_SEPARATOR(p)) 
				++p;
			printf("%s\n", p);

		}
		else {
			printf("%s\n", p);
		}
	}
}

static inline void
print_dbt(DBT *dbt_p)
{
	char buf[4096];
	int len = 0;

	if (4096 > dbt_p->size) {
		len = dbt_p->size;
	}
	else {
		len = 4096 - 1;
	}

	memcpy(buf, dbt_p->data, len);
	buf[len] = '\0';

	fprintf(stderr, "[%d %s]", len, buf);
}

static inline void
println_dbt(DBT *dbt_p)
{
	print_dbt(dbt_p);
	fprintf(stderr, "\n");
}
