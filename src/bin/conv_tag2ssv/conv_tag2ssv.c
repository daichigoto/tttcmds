/*
 * Copyright (c) 2016,2019,2021 Daichi GOTO
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

#define BUFLEN  65536

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "hvD", CMDARGS_R_NONE);

	int	rfd;
	int	wfd;

	ssize_t	nr, nw;
	int	off;

	char	buf[BUFLEN];
	char	*p;

	bool	outputed;	// Holds whether data is output or not
	bool	tagremoved;	// Holds whether tag is removed or not

	wfd = fileno(stdout);

	/*
	 * Process the first file
	 */
	FILEPROCESS_OPEN(rfd, F_ARGV[1], O_RDONLY)

	tagremoved = false;
	outputed = false;
	nw = 0;
	while ((nr = read(rfd, buf, BUFLEN)) > 0) {
		for (off = 0; nr; nr -= nw, off += nw) {
			// Skip tags
			if (!tagremoved) {
				p = buf;
				while ('\n' != *p && '\0' != *p) {
					++p;
					++off;
				}
				if ('\n' == *p) {
					++off;
					tagremoved = true;
				}
				nr -= off;
			}

			// If the read data is all tags, move to the next 
			// read without outputting
			if (0 >= nr)
				break;

			if ((nw = write(wfd, buf + off, (size_t)nr)) < 0)
				err(1, "stdout");
			outputed = true;
		}
	}

	// If there is no line feed at the end of the file, an additional 
	// line break is output.
	if (outputed && '\n' != buf[off + nr - 1])
		putchar('\n');

	close(rfd);

	// Flush the standard output before processing the next file. 
	// If this processing is not performed, the output may go wrong.
	fflush(stdout);

	/*
	 * Process second and subsequent files
	 */
	for (int file_i = 2; file_i <= F_ARGC; file_i++) {
		FILEPROCESS_OPEN(rfd, F_ARGV[file_i], O_RDONLY)

		outputed = false;
		nw = 0;
		while ((nr = read(rfd, buf, BUFLEN)) > 0) {
			for (off = 0; nr; nr -= nw, off += nw) {
				if ((nw = write(wfd, buf + off, 
						(size_t)nr)) < 0)
					err(1, "stdout");
				outputed = true;
			}
		}

		// If there is no line feed at the end of the file, an 
		// additional line break is output.
		if (outputed && '\n' != buf[off + nr - 1])
			putchar('\n');

		close(rfd);

		// Flush the standard output before processing the next 
		// file.  If this processing is not performed, the output 
		// may go wrong.
		fflush(stdout);
	}

	exit(EX_OK);
}
