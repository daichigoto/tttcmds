/*
 * Copyright (c) 2016,2019 Daichi GOTO
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

#define VERSION "20190808"
#define CMDNAME "embed_value1txt"
#define ALIAS "val1txt"

#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#ifdef __linux__
#include <db_185.h>
#else
#include <db.h>
#endif

#include "ttt.h"

#define TGT_BUFFER_PROCESS(BUF,SIZE) \
	int match; \
	for (int i = 0; i < SIZE; i++) { \
		match = 0; \
		while (0 == hashtable->seq(hashtable, \
			&hash_key, &hash_val, R_NEXT)) { \
			if (0 == strncmp(&BUF[i], hash_key.data, \
				hash_key.size-1)) { \
				printf("%s", hash_val.data); \
				i += hash_key.size - 2; \
				match = 1; \
				break; \
			} \
		} \
		if (!match) \
			putchar(BUF[i]); \
	}
