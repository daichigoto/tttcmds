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

#define VERSION "20170113"
#define CMDNAME "gyo_select"
#define ALIAS "gyosel row_select"

#include <limits.h>
#ifdef __linux__
#include <db_185.h>
#else
#include <db.h>
#endif

#include "ttt.h"

#define TGT_RETU_PROCESS(BUF,BUFLEN,INDEX) \
	fp_no_output = 1; \
	hash_key.data = BUF; \
	hash_key.size = strlen(hash_key.data) + 1; \
	hash_val.data = "1"; \
	hash_val.size = 2; \
	hashtables[i]->put(hashtables[i], &hash_key, &hash_val, 0);

#define NOTGT_RETU_PROCESS(BUF,BUFLEN,INDEX) \
	fp_no_output = 1; \

#define END_OF_LINE_RETU_PROCESS

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	if (!FLAG_o) { \
		if (NF < R_ARGV_MAX) \
			goto gyo_not_match; \
		for (int i = 1; i <= R_ARGC; i++) { \
			if (NULL != hashtables[i]) { \
				hash_key.data = GYO_BUFFER[R_ARGV[i]]; \
				hash_key.size = strlen(hash_key.data) + 1; \
				if (1 == hashtables[i]->get(hashtables[i], \
					&hash_key, &hash_val, 0)) \
					goto gyo_not_match; \
			} \
			else { \
				if (FLAG_N) { \
					n1 = strtoll(GYO_BUFFER[R_ARGV[i]],\
						(char **)NULL, 10); \
					if (0 == n1 && \
						EINVAL == errno) \
						usage(); \
					n2 = strtoll(R_ARGV_ARG1[i], \
						(char **)NULL, 10); \
					if (0 == n2 && \
						EINVAL == errno) \
						usage(); \
					cmpret = 0; \
					if (n1 > n2) \
						cmpret = 1; \
					else if (n1 < n2) \
						cmpret = -1; \
				} \
				else \
					cmpret = \
					strcmp(GYO_BUFFER[R_ARGV[i]], \
						R_ARGV_ARG1[i]); \
				switch (R_ARGV_DELIM[i]) { \
				case '>': \
					if (cmpret <= 0) \
						goto gyo_not_match; \
					break; \
				case '<': \
					if (cmpret >= 0) \
						goto gyo_not_match; \
					break; \
				default: \
					if (0 != cmpret) \
						goto gyo_not_match; \
					break; \
				} \
			} \
		} \
		goto gyo_match; \
	} \
	else { \
		for (int i = 1; i <= R_ARGC; i++) { \
			if (NULL != hashtables[i]) { \
				hash_key.data = GYO_BUFFER[R_ARGV[i]]; \
				hash_key.size = strlen(hash_key.data) + 1; \
				if (0 == hashtables[i]->get(hashtables[i], \
					&hash_key, &hash_val, 0)) \
					goto gyo_match; \
			} \
			else { \
				if (FLAG_N) { \
					n1 = strtoll(GYO_BUFFER[R_ARGV[i]],\
						(char **)NULL, 10); \
					if (0 == n1 && \
						EINVAL == errno) \
						usage(); \
					n2 = strtoll(R_ARGV_ARG1[i], \
						(char **)NULL, 10); \
					if (0 == n2 && \
						EINVAL == errno) \
						usage(); \
					cmpret = 0; \
					if (n1 > n2) \
						cmpret = 1; \
					else if (n1 < n2) \
						cmpret = -1; \
				} \
				else \
					cmpret = \
					strcmp(GYO_BUFFER[R_ARGV[i]], \
						R_ARGV_ARG1[i]); \
				switch (R_ARGV_DELIM[i]) { \
				case '>': \
					if (cmpret > 0) \
						goto gyo_match; \
					break; \
				case '<': \
					if (cmpret < 0) \
						goto gyo_match; \
					break; \
				default: \
					if (0 == cmpret) \
						goto gyo_match; \
					break; \
				} \
			} \
		} \
		goto gyo_not_match; \
	} \
gyo_match: \
	if (FLAG_n) \
		match_or_not = 0; \
	else { \
		for (int i = 1; i < NF; i++) \
			printf("%s ", GYO_BUFFER[i]); \
		printf("%s\n", GYO_BUFFER[NF]); \
	} \
gyo_not_match:
