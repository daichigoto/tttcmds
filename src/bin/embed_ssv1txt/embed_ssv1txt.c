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

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "t:nhvD", 
	           CMDARGS_R_NEED|CMDARGS_R_ARGARG_1_NEED);

	struct stat sb;
	int tsize = 0, fd, rs = 0, len = 0, match;
	char *tbuf;

	/*
	 * required option
	 */
	if (!FLAG_t)
		usage();
	if (-1 == stat(FLAG_t_ARG, &sb))
		err(errno, "%s", FLAG_t_ARG);
	
	/*
	 * template text file into the template buffer
	 */
	tsize = sb.st_size;
	tbuf = calloc(1, (tsize + 1) * sizeof(char));
	
	if (-1 == (fd = open(FLAG_t_ARG, O_RDONLY)))
		err(errno, "%s", FLAG_t_ARG);
	while (rs != tsize)
		rs += read(fd, tbuf + rs, tsize - rs);
	tbuf[tsize] = '\0';
	close(fd);

	/*
	 * FLAG_n process
	 */
	if (FLAG_n && '\n' == tbuf[tsize - 1])
		tbuf[tsize - 1] = '\0';

	FILEPROCESS_GYO

	exit(EX_OK);
}