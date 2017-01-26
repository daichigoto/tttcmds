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
	getcmdargs(argc, argv, "nhvD", 
	           CMDARGS_STDIN_TO_TMPFILE|
	           CMDARGS_R_NEED|
		   CMDARGS_R_ARGARG_1_NEED|
		   CMDARGS_R_ARGARG_2_NEED);

	/*
	 * setup the text data
	 */
	char *text[R_ARGC+1];
	int fd, rsize, key_len[R_ARGC+1];
	struct stat st;
	for (int i = 1; i <= R_ARGC; i++) {
		key_len[i] = strlen(R_ARGV_ARG1[i]);

		/*
		 * the contents of the file into the *text[]
		 */
		if (-1 == stat(R_ARGV_ARG2[i], &st))
			err(errno, "%s", R_ARGV_ARG2[i]);

		if (-1 == (fd = open(R_ARGV_ARG2[i], O_RDONLY)))
			err(errno, "%s", R_ARGV_ARG2[i]);

		text[i] = calloc(1, (st.st_size + 1) * sizeof(char));
		text[i][st.st_size] = '\0';

		rsize = 0;
		while (rsize != (int)st.st_size)
			rsize += read(fd, text[i] + rsize, 
				st.st_size - rsize);
		close(fd);

		if (FLAG_n && '\n' == text[i][st.st_size - 1])
			text[i][st.st_size - 1] = '\0';
	}

	FILEPROCESS_ALLBUFFER

	exit(EX_OK);
}
