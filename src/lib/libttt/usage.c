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

#include "ttt.h"

static char *upperstring(char *);
static char *indent(char *);
static char *spacetocomma(char *);
static int textkeyexists(const char *);

#define	OUT stderr

void
usage(void)
{
	fprintf(OUT, 
	        ES_BOLD("%s") "\n"
		"\t" ES_BOLD("%s") " - %s\n\n",
	        upperstring(gettext("name")), 
	        gettext("command_name"), gettext("command_comment"));

	fprintf(OUT,
	        ES_BOLD("%s") "\n"
		"%s\n\n", 
	        upperstring(gettext("synopsis")),
	        indent(gettext("command_synopsis")));

	fprintf(OUT,
	        ES_BOLD("%s") "\n"
	        "%s\n\n", 
	        upperstring(gettext("description")),
	        indent(gettext("command_description")));

	fprintf(OUT,
	        ES_BOLD("%s") "\n"
	        "%s\n", 
	        upperstring(gettext("options")),
	        indent(gettext("command_options")));

	if (textkeyexists("command_environment") &&
	    NULL != gettext("command_environment") &&
	    '\0' != gettext("command_environment")[0]) {
		fprintf(OUT, "\n"
		        ES_BOLD("%s") "\n"
			"%s",
		        upperstring(gettext("environment")),
		        indent(gettext("command_environment")));
	}
	if (textkeyexists("command_example") &&
	    NULL != gettext("command_example") &&
	    '\0' != gettext("command_example")[0]) {
		fprintf(OUT, "\n"
		        ES_BOLD("%s") "\n"
			"%s",
		        upperstring(gettext("example")),
		        indent(gettext("command_example")));
	}

	if (textkeyexists("command_alias") &&
	    NULL != gettext("command_alias") &&
	    '\0' != gettext("command_alias")[0]) {
		fprintf(OUT, "\n"
		        ES_BOLD("%s") "\n"
			"%s\n",
		        upperstring(gettext("alias")),
		        indent(spacetocomma(gettext("command_alias"))));
	}

	fprintf(OUT, "\n"
	        ES_BOLD("%s") "\n"
		"%s\n",
	        upperstring(gettext("copyright")),
	        indent(gettext("command_copyright")));

	exit(EX_USAGE);
}

void
version(void)
{
	fprintf(OUT, ES_BOLD("%s") "\n\t%s\n",
	        upperstring(gettext("version")),
	        gettext("command_version"));

	exit(EX_USAGE);
}

static char *
upperstring(char *text)
{
	static char buf[BUFFER_SIZE];
	char *p = text;

	for (int i = 0; i < BUFFER_SIZE - 1; i++, p++) {
		buf[i] = toupper(*p);

		if ('\0' == *p)
			break;
	}

	return buf;
}

static char *
indent(char *text)
{
	static char buf[BUFFER_SIZE];
	char *p = text;

	int i = 0;
	if ('\0' != *p)
		buf[i++] = '\t';

	for (; i < BUFFER_SIZE - 1; i++, p++) {
		buf[i] = *p;

		if ('\n' == *p)
			buf[++i] = '\t';
		if ('\0' == *p)
			break;
	}

	return buf;
}

static char *
spacetocomma(char *text)
{
	static char buf[BUFFER_SIZE];
	char *p = text;

	for (int i = 0; i < BUFFER_SIZE - 1; i++, p++) {
		if (' ' == *p) {
			buf[i] = ',';
			++i;
			buf[i] = ' ';
		}
		else
			buf[i] = *p;

		if ('\0' == *p)
			break;
	}

	return buf;
}

static int 
textkeyexists(const char *key)
{
	const char *lang_en = "en_";
	char *lang = getenv("LANG");
	struct textset *tp;

	if (NULL == lang)
		lang = "en_";

	for (int i = 0; NULL != textsets[i]; i++) {
		tp = textsets[i];
		for (int j = 0; NULL != tp[j].key; j++) {
			if (0 == strcmp(key, tp[j].key)) {
				if (0 == strncmp(lang,
					tp[j].locale, strlen(lang))) {
					return 1;
				}
				else if (0 == strncmp(lang_en,
					tp[j].locale, strlen(lang))) {
					return 1;
				}
			}
		}
	}

	return 0;
}
