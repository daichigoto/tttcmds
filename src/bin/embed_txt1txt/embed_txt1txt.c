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
	getcmdargs(argc, argv, "nhvD", 
	           CMDARGS_STDIN_TO_TMPFILE|
	           CMDARGS_R_NEED|
		   CMDARGS_R_ARGARG_1_NEED|CMDARGS_R_ARGARG_2_NEED);

	/*
	 * setup the label and value sets
	 */
        DB *hashtable;
        DBT hash_key, hash_val;
	int fd, rsize;
	struct stat st;
	char *buf;
	hashtable = dbopen(NULL, O_CREAT|O_RDWR, 0644, DB_HASH, NULL);
	for (int i = 0; i < R_ARGC; i++) {
		hash_key.data = cmdargs.r_argv_arg1[i+1];
		hash_key.size = strlen(hash_key.data) + 1;

		/*
		 * the contents of the file into the hashtable
		 */
		if (-1 == stat(cmdargs.r_argv_arg2[i+1], &st))
			err(errno, "%s", cmdargs.r_argv_arg2[i+1]);
		hash_val.size = st.st_size + 1;
		if (-1 == (fd = open(cmdargs.r_argv_arg2[i+1], O_RDONLY)))
			err(errno, "%s", cmdargs.r_argv_arg2[i+1]);
		buf = calloc(1, hash_val.size * sizeof(char));
		rsize = 0;
		while (rsize != (int)hash_val.size - 1)
			rsize += read(fd, buf + rsize,
				hash_val.size - 1 - rsize);
		close(fd);
		hash_val.data = buf;

		/*
		 * option -n process
		 */
		if (FLAG_n && '\n' == buf[hash_val.size - 2]) {
			buf[hash_val.size - 2] = '\0';
			hash_val.size -= 1;
		}
		
		hashtable->put(hashtable, &hash_key, &hash_val, 0);
	}

	FILEPROCESS_ALLBUFFER

	exit(EX_OK);
}
