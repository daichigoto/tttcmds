/*
 * Copyright (c) 2016,2017,2018,2019,2021 Daichi GOTO
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

#define VERSION "20190112"
#define CMDNAME "retu_dateformat"
#define ALIAS "dateformat datefmt"

#ifdef __linux__
#define _XOPEN_SOURCE
typedef unsigned char u_char;
#endif

#include "ttt.h"

#include "vary.h"

#define TGT_GYO_PROCESS(GYO_BUFFER,NF) \
	for (int i = 1; i <= NF; i++) { \
		if (GYO_BUFFER[i][0] == '\0' || \
			(GYO_BUFFER[i][0] == '@' && \
			 GYO_BUFFER[i][1] == '\0')) { \
			 putchar('@'); \
		} \
		else if (!R_INDEX_EXIST[i]) { \
			printf("%s", GYO_BUFFER[i]); \
		} \
		else { \
			index = R_INDEX_TO_ARGV[i]; \
			/*
			 * buffer preparation
			 */ \
			if (str_len < (int)strlen(GYO_BUFFER[i])) { \
				str_len = strlen(GYO_BUFFER[i]); \
				free(str); \
				str = calloc(str_len + 1, \
				  	sizeof(char)); \
			} \
			outfmt_len = \
				strlen(R_ARGV_ARG2[index]); \
			if (ssvstr_len < outfmt_len * 2) { \
				ssvstr_len = outfmt_len * 2; \
				free(ssvstr); \
				ssvstr = calloc(ssvstr_len + 1, \
					sizeof(char)); \
			} \
			ssvstr2str(str, GYO_BUFFER[i]); \
			/*
			 * str to struct tm
			 */ \
			HOURS30_INPUT_PRE(R_ARGV_ARG1[index]) \
			p = strptime(str, R_ARGV_ARG1[index], &tm); \
			if (FLAG_D) { \
				PRINT_STRUCT_TM(tm); \
			} \
			HOURS30_INPUT_POST \
			if (NULL == p) { \
				if (FLAG_e) \
					printf("%s", GYO_BUFFER[i]); \
				else \
					putchar('@'); \
			} \
			else { \
				if (FLAG_3) { \
					HOURS30_OUTPUT_PRE(GYO_BUFFER) \
				} \
				if (NULL != R_ARGV_ARG3[index]) { \
					v = vary_append(v, \
						R_ARGV_ARG3[index]); \
					vary_apply(v, &tm); \
					vary_destroy(v); \
					v = NULL; \
				} \
				/* If the member values of structtm are */ \
				/* inappropriate, convert them to */ \
				/* appropriate data. */ \
				mktime(&tm); \
				(void)strftime(str, str_len, \
					R_ARGV_ARG2[index], &tm); \
				if (FLAG_3) { \
					HOURS30_OUTPUT_POST( \
						R_ARGV_ARG2[index]) \
				} \
				str2ssvstr(ssvstr, str); \
				printf("%s", ssvstr); \
			} \
		} \
		if (i == NF) \
			putchar('\n'); \
		else \
			putchar(' '); \
	}

#define HOURS30_INPUT_PRE(FMT) \
	if (FLAG_D) { \
		fprintf(stderr, "HOURS30_INPUT_PRE(FMT): %s\n", FMT); \
	} \
	varry[1] = '0'; \
	INDEX_OF_HH(FMT); \
	if (indexH >= 0 && (int)strlen(str) >= indexH + 2) { \
		strncpy(tgtH, str + indexH, 2); \
		H = (int)strtol(tgtH, (char **)NULL, 10); \
		if (H > 23) { \
			sprintf(tgtH, "%02d", H - 24 * (H / 24)); \
			strncpy(str + indexH, tgtH, 2); \
			switch (H / 24) { \
			case 1: \
				varry[1] = '1'; \
				break; \
			case 2: \
				varry[1] = '2'; \
				break; \
			case 3: \
				varry[1] = '3'; \
				break; \
			case 4: \
				varry[1] = '4'; \
				break; \
			} \
		} \
	}

#define HOURS30_INPUT_POST \
	if (FLAG_D) { \
		fprintf(stderr, "HOURS30_INPUT_POST():\n"); \
	} \
	v = vary_append(v, varry); \
	vary_apply(v, &tm); \
	vary_destroy(v); \
	v = NULL;

#define HOURS30_OUTPUT_PRE(GYO_BUFFER) \
	if (FLAG_D) { \
		fprintf(stderr, "HOURS30_OUTPUT_PRE(GYO_BUFFER): %s\n", \
		        GYO_BUFFER[index_30hbase]); \
	} \
	hours30_output = 0; \
	p_base = strptime(GYO_BUFFER[index_30hbase], "%Y%m%d", \
		&tm_tomorrow); \
	if (NULL != p_base) { \
		/* base date + 1day */ \
		v = vary_append(v, "+1d"); \
		vary_apply(v, &tm_tomorrow); \
		vary_destroy(v); \
		v = NULL; \
		/* If the member values of structtm are inappropriate, */ \
		/* convert them to appropriate data. */ \
		mktime(&tm_tomorrow); \
		(void)strftime(basedate, 9, "%Y%m%d", &tm_tomorrow); \
		basedate[8] = '\0'; \
		\
		/* If the member values of structtm are inappropriate, */ \
		/* convert them to appropriate data. */ \
		mktime(&tm); \
		/* target date */ \
		(void)strftime(tgtdate, 9, "%Y%m%d", &tm); \
		tgtdate[8] = '\0'; \
		\
		if (FLAG_D) { \
			fprintf(stderr, "HOURS30_OUTPUT_PRE(GYO_BUFFER): " \
				        "basedate + 1d: %s\n", basedate); \
			fprintf(stderr, "HOURS30_OUTPUT_PRE(GYO_BUFFER): " \
				        "tgtdate      : %s\n", tgtdate); \
		} \
		if (0 == strcmp(basedate, tgtdate)) { \
			hours30_output = 1; \
			v = vary_append(v, "-1d"); \
			vary_apply(v, &tm); \
			vary_destroy(v); \
			v = NULL; \
		} \
	}

#define HOURS30_OUTPUT_POST(FMT) \
	if (FLAG_D) { \
		fprintf(stderr, "HOURS30_OUTPUT_POST(FMT): %s\n", FMT); \
		fprintf(stderr, "HOURS30_OUTPUT_POST(FMT): indexH: %d\n", \
		                 indexH); \
		fprintf(stderr, "HOURS30_OUTPUT_POST(FMT): str: %s\n", \
		                 str); \
	} \
	if (indexH >= 0 && hours30_output) { \
		(void)strftime(tgtH, 2, "%H", &tm); \
		tgtH[2] = '\0'; \
		H = (int)strtol(tgtH, (char **)NULL, 10) + 24; \
		sprintf(tgtH, "%02d", H); \
		INDEX_OF_HH(FMT); \
		if (indexH >= 0) \
			strncpy(str + indexH, tgtH, 2); \
	} \
	if (FLAG_D) { \
		fprintf(stderr, "HOURS30_OUTPUT_POST(FMT): str: %s\n", str); \
	}

#define INDEX_OF_HH(FMT) \
	ptr = strstr(FMT, "%H"); \
	if (FLAG_D) { \
		fprintf(stderr, "INDEX_OF_HH(FMT): " \
		                "ptr = strstr(FMT, \"%%H\")\n"); \
		fprintf(stderr, "INDEX_OF_HH(FMT): ptr: %s\n", ptr); \
	} \
	indexH = 0; \
	if (NULL != ptr) { \
		loopend = 0; \
		ptr2 = FMT; \
		while (*ptr2 != '\0' && !loopend) { \
			switch (*ptr2) { \
			case '%': \
				++ptr2; \
				switch (*ptr2) { \
				case 'H': \
					loopend = 1; \
					break; \
				case 'u': case 'w': case '%': \
					++indexH; \
					++ptr2; \
					break; \
				case 'd': case 'e': case 'g': case 'I': \
				case 'k': case 'l': case 'M': case 'm': \
				case 'S': case 't': case 'U': case 'V': \
				case 'W': case 'y': \
					indexH += 2; \
					++ptr2; \
					break; \
				case 'j': \
					indexH += 3; \
					++ptr2; \
					break; \
				case 'G': case 'Y': \
					indexH += 4; \
					++ptr2; \
					break; \
				} \
				break; \
			default: \
				++indexH; \
				++ptr2; \
				break; \
			} \
		} \
	} \
	else \
		indexH = -1; \
	if (FLAG_D) { \
		fprintf(stderr, "INDEX_OF_HH(FMT): indexH: %d\n", indexH); \
	}

#define PRINT_STRUCT_TM(TM) \
	fprintf(stderr, "STRUCT_TM "); \
	fprintf(stderr, "%d/%d/%d ", TM.tm_year, TM.tm_mon, TM.tm_mday); \
	fprintf(stderr, "%d:%d:%d\n", TM.tm_hour, TM.tm_min, TM.tm_sec);
