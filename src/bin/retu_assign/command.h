/*
 * Copyright (c) 2016,2017,2019 Daichi GOTO
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
#define CMDNAME "retu_assign"
#define ALIAS "assign col_assign"

#include "ttt.h"
#include "retu_assign.h"

#define DO_NOTHING			0x0001
#define DO_ASSIGN_WITH_F		0x0002
#define DO_ASSIGN_WITHOUT_F		0x0004
#define DO_MATCH_SWAP			0x0008
#define DO_NOTMATCH_SWAP		0x0010
#define	DO_JOIN				0x0020

/*
 * argument process (argument process for join)
 */
#define TGT_GYO_PROCESS(GYO_BUFFER,NF) { \
	value_len = 0; \
	for (int j = 2; j < R_ARGC; j++) \
		if (R_ARGV[j] > NF || NULL == GYO_BUFFER[R_ARGV[j]]) \
			value_len += 2; \
		else \
			value_len += strlen(GYO_BUFFER[R_ARGV[j]]) + 1; \
	if (R_ARGV[R_ARGC] > NF || NULL == GYO_BUFFER[R_ARGV[R_ARGC]]) \
		value_len += 1; \
	else \
		value_len += strlen(GYO_BUFFER[R_ARGV[R_ARGC]]); \
	value = malloc((value_len + 1) * sizeof(char)); \
	buf_len = 0; \
	v_p = value; \
	for (int j = 2; j < R_ARGC; j++) \
		if (R_ARGV[j] > NF || NULL == GYO_BUFFER[R_ARGV[j]]) { \
			strncpy(v_p, "@ ", 2); \
			v_p += 2; \
		} \
		else { \
			buf_len = strlen(GYO_BUFFER[R_ARGV[j]]); \
			strncpy(v_p, GYO_BUFFER[R_ARGV[j]], buf_len); \
			v_p += buf_len; \
			strncpy(v_p, " ", 1); \
			v_p += 1; \
		} \
	if (R_ARGV[R_ARGC] > NF || NULL == GYO_BUFFER[R_ARGV[R_ARGC]]) { \
		strncpy(v_p, "@", 1); \
		v_p += 1; \
	} \
	else { \
		buf_len = strlen(GYO_BUFFER[R_ARGV[R_ARGC]]); \
		strncpy(v_p, GYO_BUFFER[R_ARGV[R_ARGC]], buf_len); \
		v_p += buf_len; \
	} \
	strncpy(v_p, "\0", 1); \
	b_key.data = GYO_BUFFER[R_ARGV[1]]; \
	b_key.size = strlen(b_key.data) + 1; \
	b_val.data = value; \
	b_val.size = value_len + 1; \
	btrees[i]->put(btrees[i], &b_key, &b_val, 0); \
}

/*
 * retu_assign main process
 */
#define TGT_RETU_PROCESS(BUF,BUFLEN,I) { \
	if (mode[I]&DO_ASSIGN_WITH_F) \
		TGT_RETU_PROCESS_DO_ASSIGN_WITH_F(BUF,BUFLEN,I) \
	else if (mode[I]&DO_ASSIGN_WITHOUT_F) \
		TGT_RETU_PROCESS_DO_ASSIGN_WITHOUT_F(BUF,BUFLEN,I) \
	else if (mode[I]&(DO_MATCH_SWAP|DO_NOTMATCH_SWAP)) \
		TGT_RETU_PROCESS_DO_SWAP(BUF,BUFLEN,I) \
	else if (mode[I]&DO_JOIN) \
		TGT_RETU_PROCESS_DO_JOIN(BUF,BUFLEN,I) \
	else \
		NOTGT_RETU_PROCESS(BUF,BUFLEN,I) \
}

#define NOTGT_RETU_PROCESS(BUF,BUFLEN,I) \
	printf("%s",BUF);

#define END_OF_LINE_RETU_PROCESS

/*
 * assign process with -f
 */
#define TGT_RETU_PROCESS_DO_ASSIGN_WITH_F(BUF,BUFLEN,I) \
	printf("%s", a_array[i_to_ai[R_INDEX_TO_ARGV[I]]]);

/*
 * assign process without -f
 */
#define TGT_RETU_PROCESS_DO_ASSIGN_WITHOUT_F(BUF,BUFLEN,I) \
	if (FLAG_s) { \
		printf("%s", _ssvstr2str( \
			R_ARGV_ARG1[R_INDEX_TO_ARGV[I]])); \
	} \
	else { \
		printf("%s", R_ARGV_ARG1[R_INDEX_TO_ARGV[I]]); \
	}

/*
 * swap process
 */
#define TGT_RETU_PROCESS_DO_SWAP(BUF,BUFLEN,I) { \
	if (mode[I]&DO_MATCH_SWAP && \
		0 == strcmp(BUF,R_ARGV_ARG1[R_INDEX_TO_ARGV[I]])) \
		printf("%s",matchswap[I]); \
	else if (mode[I]&DO_NOTMATCH_SWAP && \
		0 != strcmp(BUF,R_ARGV_ARG1[R_INDEX_TO_ARGV[I]])) \
		printf("%s",notmatchswap[I]); \
	else \
		printf("%s",BUF); \
}

/*
 * join process
 */
#define TGT_RETU_PROCESS_DO_JOIN(BUF,BUFLEN,I) { \
	b_key.data = BUF; \
	b_key.size = strlen(BUF) + 1; \
  	memset(&b_val, 0, sizeof(DBT)); \
	if (0 == btrees[I]->get(btrees[I], \
		&b_key, &b_val, 0)) { \
		printf("%s",(char *)(b_val.data)); \
	} \
	else { \
		b_key.data = "\0"; \
		b_key.size = 1; \
		btrees[I]->get(btrees[I], \
			&b_key, &b_val, 0); \
		printf("%s",(char *)(b_val.data)); \
	} \
}
