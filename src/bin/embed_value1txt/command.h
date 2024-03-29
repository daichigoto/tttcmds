/*
 * Copyright (c) 2016,2019,2021,2023 Daichi GOTO
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

#define VERSION "20230324"
#define CMDNAME "embed_value1txt"
#define ALIAS "val1txt"

#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#if defined(__MSYS__) || defined(__linux__)
#include <db_185.h>
#else
#include <db.h>
#endif

#include "ttt.h"

#define TGT_BUFFER_PROCESS(BUF,SIZE) \
	int match; \
	int res; \
	for (int i = 0; i < SIZE; i++) { \
		match = 0; \
		for (res = db->seq(db, &key, &val, R_FIRST); \
		     0 == res; \
		     res = db->seq(db, &key, &val, R_NEXT)) { \
			if (0 == strncmp(&BUF[i], key.data, key.size-1)) { \
				printf("%s", (char *)(val.data)); \
				i += key.size - 2; \
				match = 1; \
				break; \
			} \
		} \
		if (!match) \
			putchar(BUF[i]); \
	}
