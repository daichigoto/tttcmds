/*
 * Copyright (c) 2016 Daichi GOTO
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

void
setcmdargs_from_FILENAME_RETU_RETU(struct tttcmdargs *ca,
	char *filename, char *keyretu, char *valretu, char delim)
{
	struct tttcmdargs org_args;
	char *tgts;
	int keyretu_len = strlen(keyretu);
	int valretu_len = strlen(valretu);
	int r_argc;

	for (int i = 0; i < valretu_len; i++)
		if (('/' != valretu[i]) &&
			(valretu[i] < '0' || '9' < valretu[i]))
			valretu[i] = delim;
		
	tgts = malloc(sizeof(char) * 
			(keyretu_len + 1 + valretu_len + 1));

	strncpy(tgts, keyretu, keyretu_len);
	tgts[keyretu_len] = delim; 
	strncpy(tgts + keyretu_len + 1, valretu, valretu_len + 1);
	r_argc = retucnt(tgts);

	char *r_argv[r_argc + 3];
	r_argv[0] = "";
	strtoargv(r_argv, tgts);
	free(tgts);
	r_argv[r_argc + 1] = filename;
	r_argv[r_argc + 2] = NULL;

	org_args = cmdargs;
	getcmdargs(r_argc + 2, r_argv, "", CMDARGS_R_NEED);

	*ca = cmdargs;
	cmdargs = org_args;
}
