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

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "hvD",
	           CMDARGS_R_NONE|
		   CMDARGS_STDIN_TO_TMPFILE);

	int retu = 0, retumax = -1;
	char p;
	FILEPROCESS_CHAR

	struct ssvline ssv_firstline;
	struct ssvline *p_ssvline;

	p_ssvline = &ssv_firstline;
	p_ssvline->data = NULL;
	p_ssvline->next = NULL;
	p_ssvline->nf = 0;
	p_ssvline->outputed = 0;

	FILEPROCESS_GYO

	getcmdargs_unlinktmpf();

	for (int i = 1; i <= retumax; i++) {
		p_ssvline = ssv_firstline.next;
		while (NULL != p_ssvline) {
			printf("%s", p_ssvline->data[i]);
			p_ssvline = p_ssvline->next;
			if (NULL == p_ssvline)
				printf("\n");
			else
				printf(" ");
		}
	}

	exit(EX_OK);
}
