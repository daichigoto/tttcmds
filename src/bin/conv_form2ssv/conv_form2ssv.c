/*
 * Copyright (c) 2017,2018 Daichi GOTO
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

static void proc_get(void);
static void proc_post(void);
static void proc_application_x_www_form_urlencoded(char *, int);
static void proc_multipart_form_data(char *, int);

static char *env_p;

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "hvD", 
	           CMDARGS_R_NONE|
		   CMDARGS_F_NONE|
		   CMDARGS_A_NONE);

	if (FLAG_D) {
		fprintf(stderr, "REQUEST_METHOD %s\n", 
				getenv("REQUEST_METHOD"));
		fprintf(stderr, "QUERY_STRING %s\n", 
				getenv("QUERY_STRING"));
		fprintf(stderr, "CONTENT_TYPE %s\n", 
				getenv("CONTENT_TYPE"));
		fprintf(stderr, "CONTENT_LENGTH %s\n", 
				getenv("CONTENT_LENGTH"));
	}

	env_p = getenv("REQUEST_METHOD");
	if (NULL == env_p) {
		env_p = getenv("CONTENT_LENGTH");
		if (NULL == env_p) {
			if (FLAG_D) 
				fprintf(stderr, "unkown\n");
			usage();
		}
		else
			proc_post();
	}
	else if (0 == strcmp("GET", env_p))
		proc_get();
	else if (0 == strcmp("POST", env_p))
		proc_post();
	else
		usage();

	exit(EX_OK);
}

static void
proc_get()
{
	if (FLAG_D) 
		fprintf(stderr, "proc_get()\n");

	env_p = getenv("QUERY_STRING");
	if (NULL == env_p)
		usage();

	proc_application_x_www_form_urlencoded(env_p, strlen(env_p));
}

static void
proc_post()
{
	if (FLAG_D) 
		fprintf(stderr, "proc_post()\n");

	char *content_length = getenv("CONTENT_LENGTH");
	if (NULL == content_length) {
		fprintf(stderr, "no CONTENT_LENGTH\n");
		usage();
	}

	errno = 0;
	int bufsize = (int)strtol(content_length, (char **)NULL, 10);
	if (EINVAL == errno) {
		fprintf(stderr, "invalid CONTENT_LENGTH\n");
		usage();
	}

	char buf[bufsize + 1];
	buf[bufsize] = '\0';
	int rs = 0;
	while (rs != bufsize)
		rs += read(STDIN_FILENO, buf+rs, bufsize-rs);

	env_p = getenv("CONTENT_TYPE");
	if (NULL == env_p)
		/* Assuming that the undefined is 
		 * application/x-www-form-urlencoded */
		proc_application_x_www_form_urlencoded(buf, bufsize);
	else if (0 == strncmp("application/x-www-form-urlencoded", 
				env_p, 33))
		proc_application_x_www_form_urlencoded(buf, bufsize);
	else if (0 == strncmp("multipart/form-data", env_p, 19))
		proc_multipart_form_data(buf, bufsize);
	else
		usage();

}

static void
proc_application_x_www_form_urlencoded(char *p, int len)
{
	if (FLAG_D) 
		fprintf(stderr, 
			"proc_application_x_www_form_urlencoded()\n");

	if (0 == len)
		return;

	char buf[1+len*2];
	unsigned char c;
	char *s;
	s = buf;
	for (; *p != '\0'; p++) {
		switch (*p) {
		case '%':
			++p;
			switch (*p) {
			case '0': c =   0; break;
			case '1': c =  16; break;
			case '2': c =  32; break;
			case '3': c =  48; break;
			case '4': c =  64; break;
			case '5': c =  80; break;
			case '6': c =  96; break;
			case '7': c = 112; break;
			case '8': c = 128; break;
			case '9': c = 144; break;
			case 'A': c = 160; break;
			case 'a': c = 160; break;
			case 'B': c = 176; break;
			case 'b': c = 176; break;
			case 'C': c = 192; break;
			case 'c': c = 192; break;
			case 'D': c = 208; break;
			case 'd': c = 208; break;
			case 'E': c = 224; break;
			case 'e': c = 224; break;
			case 'F': c = 240; break;
			case 'f': c = 240; break;
			default:
				usage();
			}
			++p;
			switch (*p) {
			case '0': c +=  0; break;
			case '1': c +=  1; break;
			case '2': c +=  2; break;
			case '3': c +=  3; break;
			case '4': c +=  4; break;
			case '5': c +=  5; break;
			case '6': c +=  6; break;
			case '7': c +=  7; break;
			case '8': c +=  8; break;
			case '9': c +=  9; break;
			case 'A': c += 10; break;
			case 'a': c += 10; break;
			case 'B': c += 11; break;
			case 'b': c += 11; break;
			case 'C': c += 12; break;
			case 'c': c += 12; break;
			case 'D': c += 13; break;
			case 'd': c += 13; break;
			case 'E': c += 14; break;
			case 'e': c += 14; break;
			case 'F': c += 15; break;
			case 'f': c += 15; break;
			default:
				usage();
			}
			*s++ = c;
			break;
		case '&':
			*s = '\0';
			printf("%s\n",_str2ssvstr(buf));
			if (FLAG_D)
				fprintf(stderr, "%s\n",_str2ssvstr(buf));
			s = buf;
			break;
		case '=':
			*s = '\0';
			printf("%s ",_str2ssvstr(buf));
			if (FLAG_D)
				fprintf(stderr, "%s ",_str2ssvstr(buf));
			s = buf;
			break;
		case '+':
			*s++ = ' ';
			break;
		default:
			*s++ = *p;
			break;
		}
	}

	if (s == buf) {
		printf("@\n");
		if (FLAG_D)
			fprintf(stderr, "@\n");
	}
	else {
		*s = '\0';
		printf("%s\n",_str2ssvstr(buf));
		if (FLAG_D)
			fprintf(stderr, "%s\n",_str2ssvstr(buf));
	}
}

static void
proc_multipart_form_data(char *p, int len)
{
	if (FLAG_D) 
		fprintf(stderr, "proc_multipart_form_data()\n");

	char key[1+len], *k;
	char content[1+len], *c;
	char boundary[1+len], *b;
	int boundary_len, rs = 0;

	/*
	 * grab the boundary
	 */
	b = boundary;
	*b++ = '\r';
	*b++ = '\n';
	while ('\r' != *p) {
		*b = *p;
		++b;
		++p;
		++rs;
	}
	*b = '\0';
	p += 2;
	rs += 2;
	boundary_len = strlen(boundary);

	while ('\0' != *p) {
		/*
		 * grab the key
		 */
		while ('\0' != *p && 0 != strncasecmp("name=\"", p, 5)) {
			++p;
			++rs;
		}
		p += 6;
		rs += 6;
		k = key;
		while ('\0' != *p && '"' != *p) {
			if (*p == '%' && *(p+1) == '2' && *(p+2) == '2') {
				*k = '"';
				p += 2;
				rs += 2;
			}
			else
				*k = *p;
			++p;
			++rs;
			++k;
		}
		*k = '\0';
		printf("%s ", _str2ssvstr(key));
		if (FLAG_D)
			fprintf(stderr, "%s ", _str2ssvstr(key));
	
		/*
		 * grab the , intcontent
		 */
		while ('\0' != *p && 0 != strncmp("\r\n\r\n", p, 4)) {
			++p;
			++rs;
		}
		p += 4;
		rs += 4;
		c = content;
		while ('\0' != *p && 
			0 != strncmp(boundary, p, boundary_len)) {
			*c = *p;
			++p;
			++rs;
			++c;
		}
		*c = '\0';
		printf("%s\n", _str2ssvstr(content));
		if (FLAG_D)
			fprintf(stderr, "%s\n", _str2ssvstr(content));
		p += boundary_len;
		rs += boundary_len;

		if (rs + 4 >= len)
			break;
	}
}
