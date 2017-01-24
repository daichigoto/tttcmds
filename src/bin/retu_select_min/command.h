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

#define VERSION "20170124"
#define CMDNAME "retu_select_min"
#define ALIAS "retusel_min col_select_min"

#include "ttt.h"

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	if (FLAG_1 && first_line) \
		first_line = 0; \
	else { \
		for (int i = 1; i <= R_ARGC; i++) \
			if (R_ARGV[i] <= NF && \
				NULL != GYO_BUFFER[R_ARGV[i]]) { \
				MIN(GYO_BUFFER[R_ARGV[i]],i); \
			} \
	}

#define MIN(TARGET,I) { \
	if ('\0' != TARGET[0] && '@' != TARGET[0] && '\0' != TARGET[1]) { \
		if ('@' == min[I][0] && '\0' == min[I][1]) { \
			if (FLAG_N) { \
				errno = 0; \
				num = (int)strtol(TARGET, \
					(char **)NULL, 10); \
				if (EINVAL != errno) { \
					strcpy(min[I], \
						_str2ssvstr(TARGET)); \
					nummin[I] = num; \
				} \
			} \
			else \
				strcpy(min[I], _str2ssvstr(TARGET)); \
		} \
		else { \
			if (FLAG_N) { \
				errno = 0; \
				num = (int)strtol(TARGET, \
					(char **)NULL, 10); \
				if (EINVAL != errno) { \
					if (num < nummin[I]) { \
						strcpy(min[I], \
						_str2ssvstr(TARGET)); \
						nummin[I] = num; \
					} \
				} \
			} \
			else { \
				if (strcmp(TARGET, min[I]) < 0) \
					strcpy(min[I], \
						_str2ssvstr(TARGET)); \
			} \
		} \
	} \
}
