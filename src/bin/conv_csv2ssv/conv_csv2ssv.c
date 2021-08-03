/*
 * Copyright (c) 2021 Daichi GOTO
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

/*
 * File Format Specifications
 * ==========================
 *
 * CSV (Commma-separated values)
 * -----------------------------
 *   Request for Comments: 4180
 *   Common Format and MIME Type for Comma-Separated Values (CSV) Files
 *     https://datatracker.ietf.org/doc/html/rfc4180
 *
 *   [*] However, it does not support line feeds within a record.
 *
 * SSV (extended Space-separated values)
 * -------------------------------------
 *   Based on the below TSV, with some modifications as follows:
 *     delimiter:    [tab] -> [space]
 *     empty record: ''    -> '@'
 *     quoted chars: ' '   -> '_'
 *                   '_'   -> '\_'
 *                   '@'   -> '\@'
 *
 * TSV (Tab-separated values)
 * --------------------------
 *   Definition of tab-separated-values (tsv), Internet Assigned Numbers Authority
 *     https://www.iana.org/assignments/media-types/text/tab-separated-values 
 */
#include "command.h"

static int csv2ssv(const char *, int);
static void putssvchar(const char);
static bool record_outputed;

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "hvD", 
	           CMDARGS_STDIN_TO_TMPFILE);

	FILEPROCESS_ALLBUFFER

	exit(EX_OK);
}

static int
csv2ssv(const char *buf, int bufsize)
{
	// When the target is empty, no processing is done.
	if (0 == bufsize)
		return 0;

	const char	*p, *end;
	p = buf;
	end = &buf[bufsize - 1];

	// Indicates the state during parsing.
	typedef enum RECORD_STATUS { 
		RECORD_END,
		IN_RECORD,
		IN_QUOTED_RECORD
	} record_status;
	record_status	rs = RECORD_END;

	record_outputed = false;
	while (1) {
		if ('\n' == *p) {
			if (! record_outputed) {
				putchar('@');
			}
			rs = RECORD_END;
			putssvchar('\n');
		}
		else {
			switch (rs) {
			case RECORD_END:
				if (',' == *p) {
					putchar('@');
				}
				else if ('"' == *p) {
					rs = IN_QUOTED_RECORD;
				}
				else {
					rs = IN_RECORD;
					putssvchar(*p);
				}
				break;
			case IN_RECORD:
				if (',' == *p) {
					rs = RECORD_END;
				}
				else {
					putssvchar(*p);
				}
				break;
			case IN_QUOTED_RECORD:
				if ('"' == *p) {
					if (p == end) {
						rs = RECORD_END;
					}
					else if (',' == *(p+1)) {
						rs = RECORD_END;
						++p;
					}
					else if ('"' == *(p+1)) {
						putssvchar(*p);
						++p;
					}
				}
				else {
					putssvchar(*p);
				}
				break;
			}

			switch (rs) {
			case RECORD_END:
				putchar(' ');
				record_outputed = false;
				break;
			case IN_RECORD:
			case IN_QUOTED_RECORD:
				break;
			}
		}

		if (p == end)
			break;
		else
			++p;
	}

	return 0;
}

static void
putssvchar(const char c)
{
	if (' ' == c) {
		putchar('_');
	}
	else if ('_' == c) {
		putchar('\\');
		putchar('_');
	}
	else if ('@' == c) {
		putchar('\\');
		putchar('@');
	}
	else {
		putchar(c);
	}
	record_outputed = true;
}
