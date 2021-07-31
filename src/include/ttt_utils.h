/*
 * Copyright (c) 2016, 2019 Daichi GOTO
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

#define FILEPROCESS_RETU { \
	FILE *fp_fp; \
	int fp_no_output = 0; \
	int fp_b = 0, fp_r_i = 1; \
	int fp_buf_i, fp_buf_len; \
	char *fp_buf, *fp_p = NULL, *fp_newbuf, *fp_buf_end; \
	fp_buf_len = BUFFER_SIZE; \
	fp_buf = calloc(fp_buf_len, sizeof(char)); \
	for (int fp_file_i = 1; fp_file_i <= F_ARGC; fp_file_i++) { \
		fp_fp = fopen(F_ARGV[fp_file_i], "r"); \
		if (NULL == fp_fp) \
			err(errno, "%s", F_ARGV[fp_file_i]); \
		while (EOF != (fp_b = fgetc(fp_fp))) { \
			fp_p = fp_buf; \
			fp_buf_i = 0; \
			fp_buf_end = &fp_buf[fp_buf_len - 1]; \
			*fp_p = fp_b; \
			while (' ' != *fp_p && \
			       '\n' != *fp_p && EOF != *fp_p) { \
				++fp_p; \
				++fp_buf_i; \
				FILEPROCESS_RETU_BUFFER_EXPANSION \
				*fp_p = fgetc(fp_fp); \
			} \
			if ((' ' == fp_b && *fp_p == fp_b) || \
			    ('\n' == fp_b && *fp_p == fp_b)) { \
				*fp_p = '@'; \
				++fp_p; \
				++fp_buf_i; \
				FILEPROCESS_RETU_BUFFER_EXPANSION \
			} \
			else { \
				fp_b = *fp_p; \
			} \
			*fp_p = '\0'; \
			if (fp_r_i <= R_INDEX_MAX && \
			    R_INDEX_EXIST[fp_r_i]) { \
				TGT_RETU_PROCESS(fp_buf,fp_buf_len,fp_r_i) \
			} \
			else { \
				NOTGT_RETU_PROCESS(fp_buf,fp_buf_len,fp_r_i) \
			} \
			switch (fp_b) { \
			case ' ': \
				if (!fp_no_output) putchar(' '); \
				++fp_r_i; \
				break; \
			case '\n': \
			case EOF: \
				if (!fp_no_output) putchar('\n'); \
				fp_r_i = 1; \
				END_OF_LINE_RETU_PROCESS \
				break; \
			} \
		} \
		fclose(fp_fp); \
	} \
}

#define FILEPROCESS_RETU_BUFFER_EXPANSION { \
	if (fp_p == fp_buf_end) { \
		fp_newbuf = \
			calloc(fp_buf_len + BUFFER_SIZE, sizeof(char)); \
		if (NULL == fp_newbuf) \
			err(errno, "ttt_utils.h#FILEPROCESS_RETU"); \
		memcpy(fp_newbuf, fp_buf, fp_buf_len * sizeof(char)); \
		fp_buf_len += BUFFER_SIZE; \
		free(fp_buf); \
		fp_buf = fp_newbuf; \
		fp_buf_end = &fp_buf[fp_buf_len - 1]; \
		fp_p = &fp_buf[fp_buf_i]; \
	} \
}

#define FILEPROCESS_GYO { \
	FILE *fp_fp; \
	struct stat fp_sb; \
  int intbuf; \
	int fp_b = 0, fp_r_i = 1, fled = 0; \
	int fp_buf_i, fp_buf_len, fp_ibuf_len, fp_nf; \
	char *fp_buf, *fp_buf_end, **fp_ibuf; \
	char *fp_p = NULL, *fp_newbuf, **fp_newibuf; \
	int *r_index_to_argv, *r_index_exist, r_index_max; \
	fp_buf_len = BUFFER_SIZE; \
	fp_ibuf_len = 32; \
	fp_buf = calloc(fp_buf_len, sizeof(char)); \
	fp_ibuf = calloc(fp_ibuf_len + 1, sizeof(char *)); \
	for (int fp_file_i = 1; \
	     fp_file_i <= F_ARGC; fp_file_i++) { \
		fp_fp = fopen(F_ARGV[fp_file_i], "r"); \
		if (NULL == fp_fp) \
			err(errno, "%s", F_ARGV[fp_file_i]); \
		stat(F_ARGV[fp_file_i], &fp_sb); \
		fp_p = fp_buf; \
		fp_buf_i = fp_nf = 0; \
		fp_buf_end = &fp_buf[fp_buf_len - 1]; \
		while (1) { \
			fp_b = intbuf = fgetc(fp_fp); \
			if (EOF == fp_b) { \
				if (fled) { fled = 0; break; } \
				else fp_nf -= 1; \
			} \
			fled = 0; \
			*fp_p = fp_b; \
			while (' ' != *fp_p && \
			       '\n' != *fp_p && EOF != intbuf) { \
				++fp_p; \
				++fp_buf_i; \
				FILEPROCESS_GYO_BUFFER_EXPANSION \
				*fp_p = intbuf = fgetc(fp_fp); \
			} \
			if ((' ' == fp_b && *fp_p == fp_b) || \
			    ('\n' == fp_b && *fp_p == fp_b) || \
			    (EOF == fp_b && *fp_p == fp_b)) { \
				*fp_p = '@'; \
				++fp_p; \
				++fp_buf_i; \
				FILEPROCESS_GYO_BUFFER_EXPANSION \
			} \
			else { \
				if (EOF != fp_b) fp_b = *fp_p; \
			} \
			*fp_p = '\0'; \
			++fp_nf; \
			switch (fp_b) { \
			case ' ': \
				++fp_p; \
				++fp_buf_i; \
				FILEPROCESS_GYO_BUFFER_EXPANSION \
				++fp_r_i; \
				break; \
			case '\n': \
				fled = 1; \
			case EOF: \
				fp_r_i = 1; \
				FILEPROCESS_GYO_IBUFFER_EXPANSION \
				FILEPROCESS_GYO_IBUFFER_ASSIGN \
				FILEPROCESS_GYO_R_INDEX_EXPANSION \
				TGT_GYO_PROCESS(fp_ibuf,fp_nf) \
				fp_p = fp_buf; \
				fp_buf_i = fp_nf = 0; \
				break; \
			} \
			if (EOF == fp_b) \
				break; \
		} \
		fclose(fp_fp); \
	} \
} 

#define FILEPROCESS_GYO_FILESIZE_IS_ZERO \
	0 == fp_sb.st_size

#define FILEPROCESS_GYO_BUFFER_EXPANSION { \
	if (fp_p == fp_buf_end) { \
		fp_newbuf = \
			calloc(fp_buf_len + BUFFER_SIZE, sizeof(char)); \
		if (NULL == fp_newbuf) \
			err(errno, \
			    "ttt_utils.h#" \
			    "FILEPROCESS_GYO_BUFFER_EXPANSION"); \
		memcpy(fp_newbuf, fp_buf, fp_buf_len * sizeof(char)); \
		fp_buf_len += BUFFER_SIZE; \
		free(fp_buf); \
		fp_buf = fp_newbuf; \
		fp_buf_end = &fp_buf[fp_buf_len - 1]; \
		fp_p = &fp_buf[fp_buf_i]; \
	} \
}

#define FILEPROCESS_GYO_IBUFFER_EXPANSION { \
	if (fp_ibuf_len < fp_nf) { \
	 	fp_newibuf = calloc(fp_nf + 1, sizeof(char *)); \
		if (NULL == fp_newibuf) \
			err(errno, \
			    "ttt_utils.h#" \
			    "FILEPROCESS_GYO_IBUFFER_EXPANSION"); \
		memcpy(fp_newibuf, fp_ibuf, fp_ibuf_len * sizeof(char *)); \
		fp_ibuf_len = fp_nf; \
	 	free(fp_ibuf); \
		fp_ibuf = fp_newibuf; \
	} \
}

#define FILEPROCESS_GYO_IBUFFER_ASSIGN { \
	fp_p = fp_buf; \
	fp_ibuf[1] = fp_buf; \
	for (int fp_i = 2; fp_i <= fp_nf; fp_i++) { \
		while ('\0' != *fp_p) { \
			++fp_p; \
		} \
		++fp_p; \
		fp_ibuf[fp_i] = fp_p; \
	} \
}

#define FILEPROCESS_GYO_R_INDEX_EXPANSION { \
	if (R_INDEX_MAX < fp_nf) { \
		r_index_max = fp_nf; \
		r_index_to_argv = \
			calloc(r_index_max + 1, sizeof(int)); \
		if (NULL == r_index_to_argv) \
			err(errno, \
			    "ttt_utils.h#" \
			    "FILEPROCESS_GYO_R_INDEX_EXPANSION"); \
		memcpy(r_index_to_argv, R_INDEX_TO_ARGV, \
			(r_index_max + 1) * sizeof(int)); \
		for (int fp_i = R_INDEX_MAX + 1; \
			fp_i <= r_index_max + 1; fp_i++) \
			r_index_to_argv[fp_i] = R_INDEX_IS_NONE; \
		free(R_INDEX_TO_ARGV); \
		R_INDEX_TO_ARGV = r_index_to_argv; \
		; \
		r_index_exist = calloc(r_index_max + 1, sizeof(int)); \
		if (NULL == r_index_exist) \
			err(errno, \
			    "ttt_utils.h#" \
			    "FILEPROCESS_GYO_R_INDEX_EXPANSION"); \
		memcpy(r_index_exist, R_INDEX_EXIST, \
			(r_index_max + 1) * sizeof(int)); \
		for (int fp_i = R_INDEX_MAX + 1; \
			fp_i <=r_index_max + 1; fp_i++) \
			r_index_exist[fp_i] = R_INDEX_IS_NOT_EXISTENCE; \
		free(R_INDEX_EXIST); \
		R_INDEX_EXIST = r_index_exist; \
		R_INDEX_MAX = r_index_max; \
	} \
}

#define FILEPROCESS_CHAR { \
	FILE *fp_fp; \
	int fp_b = 0; \
	for (int fp_file_i = 1; fp_file_i <= F_ARGC; fp_file_i++) { \
		fp_fp = fopen(F_ARGV[fp_file_i], "r"); \
		if (NULL == fp_fp) \
			err(errno, "%s", F_ARGV[fp_file_i]); \
		while (1) { \
			fp_b = fgetc(fp_fp); \
			TGT_CHAR_PROCESS(fp_b) \
			if (EOF == fp_b) \
				break; \
		} \
		fclose(fp_fp); \
	} \
}

#define FILEPROCESS_CAT { \
	FILE *fp_fp; \
	int fp_b = 0; \
	char fp_bpre; \
	for (int fp_file_i = 1; fp_file_i <= F_ARGC; fp_file_i++) { \
		fp_fp = fopen(F_ARGV[fp_file_i], "r"); \
		if (NULL == fp_fp) \
			err(errno, "%s", F_ARGV[fp_file_i]); \
		while (1) { \
			fp_b = fgetc(fp_fp); \
			if (EOF == fp_b) { \
				if ('\n' != fp_bpre) \
					putchar('\n'); \
				break; \
			} \
			putchar(fp_b); \
			fp_bpre = fp_b; \
		} \
		fclose(fp_fp); \
	} \
}

#define FILEPROCESS_ALLBUFFER { \
	int fp_fd, fp_size, fp_rsize; \
	struct stat fp_st; \
	char *fp_buf; \
	for (int fp_file_i = 1; fp_file_i <= F_ARGC; fp_file_i++) { \
		if (-1 == stat(F_ARGV[fp_file_i], &fp_st )) \
			err(errno, "%s", F_ARGV[fp_file_i]); \
		fp_size = fp_st.st_size; \
		fp_buf = calloc(fp_size + 1, sizeof(char)); \
		if (-1 == (fp_fd = open(F_ARGV[fp_file_i], O_RDONLY))) \
			err(errno, "%s", F_ARGV[fp_file_i]); \
		fp_rsize = 0; \
		while (fp_rsize != fp_size) \
			fp_rsize += read(fp_fd, fp_buf+fp_rsize, \
				fp_size-fp_rsize); \
		TGT_BUFFER_PROCESS(fp_buf, fp_size) \
		free(fp_buf); \
		close(fp_fd); \
	} \
}
