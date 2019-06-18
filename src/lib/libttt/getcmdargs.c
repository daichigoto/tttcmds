/*
 * Copyright (c) 2016-2019 Daichi GOTO
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

#include "ttt.h"

struct tttcmdargs cmdargs;

#define SETFLAG(X,Y,Z) \
	Y = 1; \
	if (NULL != optargs && NULL != strstr(optargs, X)) { \
		if (':' == *(1+strstr(optargs, X))) { \
			if ('\0' == argv[i][2]) \
				Z = argv[++i]; \
			else \
				Z = &argv[i][2]; \
		} \
		else if ('!' == *(1+strstr(optargs, X))) { \
			if (exclusion) \
				usage(); \
			exclusion = 1; \
		} \
	} \
	else \
		usage();

#define REALLOC_IARRAY(OLDLEN,NEWLEN,BUF) { \
	i_ptr = realloc(BUF, sizeof(int) * (NEWLEN)); \
	if (NULL == i_ptr) \
		err(errno, "getcmdargs#REALLOC_IARRAY"); \
	memset(i_ptr + sizeof(int)*(OLDLEN), 0, \
		sizeof(int) * ((NEWLEN)-(OLDLEN))); \
	BUF = i_ptr; \
}

#define REALLOC_CARRAY(OLDLEN,NEWLEN,BUF) { \
	c_ptr = realloc(BUF, sizeof(char) * (NEWLEN)); \
	if (NULL == c_ptr) \
		err(errno, "getcmdargs#REALLOC_CARRAY"); \
	memset(c_ptr + sizeof(char)*(OLDLEN), 0, \
		sizeof(char) * ((NEWLEN)-(OLDLEN))); \
	BUF = c_ptr; \
}

#define REALLOC_SARRAY(OLDLEN,NEWLEN,BUF) { \
	c_pptr = realloc(BUF, sizeof(char *) * (NEWLEN)); \
	if (NULL == c_pptr) \
		err(errno, "getcmdargs#REALLOC_SARRAY"); \
	BUF = c_pptr; \
}

#define ARRAY_EXPANSION(OLDLEN,NEWLEN) \
	REALLOC_IARRAY(OLDLEN,NEWLEN,cmdargs.r_argv) \
	REALLOC_IARRAY(OLDLEN,NEWLEN,cmdargs.r_index_exist) \
	REALLOC_IARRAY(OLDLEN,NEWLEN,cmdargs.r_index_to_argv) \
	REALLOC_CARRAY(OLDLEN,NEWLEN,cmdargs.r_argv_delim) \
	REALLOC_SARRAY(OLDLEN,NEWLEN,cmdargs.r_argv_arg1) \
	REALLOC_SARRAY(OLDLEN,NEWLEN,cmdargs.r_argv_arg2) \
	REALLOC_SARRAY(OLDLEN,NEWLEN,cmdargs.r_argv_arg3)

#define TMPDIR_NAME			".cache/ttt/tmp"
#define TMPFILE_NAME			"temp_XXXXXX"
#define R_ARGV_MAX_INIT			256
#define R_ARGV_ADDITION_SIZE_INIT	256

static int r_argv_max = R_ARGV_MAX_INIT;
static const int r_argv_addition_size = R_ARGV_ADDITION_SIZE_INIT;
static int stdin_file_used = 0;
static char *tempfile = NULL;

static void mktempfile(void);
static void stdintotempfile(void);

int
getcmdargs(const int argc, char *argv[], const char *optargs, int flags)
{
	int i, j, k, range, *i_ptr, exclusion = 0, mincol = 1;
	int single_delimiter_mode = 0;
	int double_delimiter_mode = 0;
	int triple_delimiter_mode = 0;
	char buf[BUFFER_SIZE], *p1, *p2, delim, *c_ptr, **c_pptr, o;

	if (flags&CMDARGS_R_MINIMUMNUM_IS_0)
		mincol = 0;

	if (flags&CMDARGS_DELIMITER_ONLY_1)
		single_delimiter_mode = 1;
	if (flags&CMDARGS_DELIMITER_ONLY_2)
		double_delimiter_mode = 1;
	if (flags&CMDARGS_DELIMITER_ONLY_3)
		triple_delimiter_mode = 1;

	/*
	 * cmdargs initialization
	 */
	memset(&cmdargs, 0, sizeof(struct tttcmdargs));

	cmdargs.f_argc = 0;
	cmdargs.f_argv = calloc(1, 2 * sizeof(char *));

	cmdargs.a_argc = 0;
	cmdargs.a_argv = calloc(1, 2 * sizeof(char *));

	cmdargs.r_argv_max = 0;
	cmdargs.r_argv = calloc(1, r_argv_max * sizeof(int));
	cmdargs.r_argv_arg1 = calloc(1, r_argv_max * sizeof(char *));
	cmdargs.r_argv_arg2 = calloc(1, r_argv_max * sizeof(char *));
	cmdargs.r_argv_arg3 = calloc(1, r_argv_max * sizeof(char *));
	cmdargs.r_argv_delim = calloc(1, r_argv_max * sizeof(char));
	cmdargs.r_index_exist = calloc(1, r_argv_max * sizeof(int));
	cmdargs.r_index_to_argv = calloc(1, r_argv_max * sizeof(int));
	for (i = 0; i < r_argv_max; i++) {
		cmdargs.r_argv[i] = -1;
		cmdargs.r_index_exist[i] = R_INDEX_IS_NOT_EXISTENCE;
		cmdargs.r_index_to_argv[i] = R_INDEX_IS_NONE;
	}	
	cmdargs.r_index_max = 0;
	/*
	 * Command name
	 */
	cmdargs.cmdname = argv[0];
	cmdargs.r_argc = 0;

	/*
	 * Options analysis
	 */
	i = 1;
	while (i < argc) {
		switch (argv[i][0]) {
		case '-':
			j = 1;
			o = argv[i][j];
			switch (o) {
			case '-':
				// -- : End of options
				++i;
				goto retu_analysis;
			case '\0':
				// - : stdin
				if (!(flags&CMDARGS_F_NONE)) {
					cmdargs.f_argv[1] = STDIN_FILE;
					stdin_file_used = 1;
					cmdargs.f_argc += 1;
					++i;
					goto file_analysis;
				}
				// - : arg
				else if (!(flags&CMDARGS_A_NONE)) {
					cmdargs.a_argv[1] = "-";
					cmdargs.a_argc += 1;
					++i;
					goto argarg_analysis;
				}
			case 'a': SETFLAG("a", FLAG_a, FLAG_a_ARG); break;
			case 'b': SETFLAG("b", FLAG_b, FLAG_b_ARG); break;
			case 'c': SETFLAG("c", FLAG_c, FLAG_c_ARG); break;
			case 'd': SETFLAG("d", FLAG_d, FLAG_d_ARG); break;
			case 'e': SETFLAG("e", FLAG_e, FLAG_e_ARG); break;
			case 'f': SETFLAG("f", FLAG_f, FLAG_f_ARG); break;
			case 'g': SETFLAG("g", FLAG_g, FLAG_g_ARG); break;
			case 'h': SETFLAG("h", FLAG_h, FLAG_h_ARG);
			          usage();                          break;
			case 'i': SETFLAG("i", FLAG_i, FLAG_i_ARG); break;
			case 'j': SETFLAG("j", FLAG_j, FLAG_j_ARG); break;
			case 'k': SETFLAG("k", FLAG_k, FLAG_k_ARG); break;
			case 'l': SETFLAG("l", FLAG_l, FLAG_l_ARG); break;
			case 'm': SETFLAG("m", FLAG_m, FLAG_m_ARG); break;
			case 'n': SETFLAG("n", FLAG_n, FLAG_n_ARG); break;
			case 'o': SETFLAG("o", FLAG_o, FLAG_o_ARG); break;
			case 'p': SETFLAG("p", FLAG_p, FLAG_p_ARG); break;
			case 'q': SETFLAG("q", FLAG_q, FLAG_q_ARG); break;
			case 'r': SETFLAG("r", FLAG_r, FLAG_r_ARG); break;
			case 's': SETFLAG("s", FLAG_s, FLAG_s_ARG); break;
			case 't': SETFLAG("t", FLAG_t, FLAG_t_ARG); break;
			case 'u': SETFLAG("u", FLAG_u, FLAG_u_ARG); break;
			case 'v': SETFLAG("v", FLAG_v, FLAG_v_ARG); 
			          version();                        break;
			case 'w': SETFLAG("w", FLAG_w, FLAG_w_ARG); break;
			case 'x': SETFLAG("x", FLAG_x, FLAG_x_ARG); break;
			case 'y': SETFLAG("y", FLAG_y, FLAG_y_ARG); break;
			case 'z': SETFLAG("z", FLAG_z, FLAG_z_ARG); break;
			case 'A': SETFLAG("A", FLAG_A, FLAG_A_ARG); break;
			case 'B': SETFLAG("B", FLAG_B, FLAG_B_ARG); break;
			case 'C': SETFLAG("C", FLAG_C, FLAG_C_ARG); break;
			case 'D': SETFLAG("D", FLAG_D, FLAG_D_ARG); break;
			case 'E': SETFLAG("E", FLAG_E, FLAG_E_ARG); break;
			case 'F': SETFLAG("F", FLAG_F, FLAG_F_ARG); break;
			case 'G': SETFLAG("G", FLAG_G, FLAG_G_ARG); break;
			case 'H': SETFLAG("H", FLAG_H, FLAG_H_ARG); break;
			case 'I': SETFLAG("I", FLAG_I, FLAG_I_ARG); break;
			case 'J': SETFLAG("J", FLAG_J, FLAG_J_ARG); break;
			case 'K': SETFLAG("K", FLAG_K, FLAG_K_ARG); break;
			case 'L': SETFLAG("L", FLAG_L, FLAG_L_ARG); break;
			case 'M': SETFLAG("M", FLAG_M, FLAG_M_ARG); break;
			case 'N': SETFLAG("N", FLAG_N, FLAG_N_ARG); break;
			case 'O': SETFLAG("O", FLAG_O, FLAG_O_ARG); break;
			case 'P': SETFLAG("P", FLAG_P, FLAG_P_ARG); break;
			case 'Q': SETFLAG("Q", FLAG_Q, FLAG_Q_ARG); break;
			case 'R': SETFLAG("R", FLAG_R, FLAG_R_ARG); break;
			case 'S': SETFLAG("S", FLAG_S, FLAG_S_ARG); break;
			case 'T': SETFLAG("T", FLAG_T, FLAG_T_ARG); break;
			case 'U': SETFLAG("U", FLAG_U, FLAG_U_ARG); break;
			case 'V': SETFLAG("V", FLAG_V, FLAG_V_ARG); break;
			case 'W': SETFLAG("W", FLAG_W, FLAG_W_ARG); break;
			case 'X': SETFLAG("X", FLAG_X, FLAG_X_ARG); break;
			case 'Y': SETFLAG("Y", FLAG_Y, FLAG_Y_ARG); break;
			case 'Z': SETFLAG("Z", FLAG_Z, FLAG_Z_ARG); break;
			case '0': SETFLAG("0", FLAG_0, FLAG_0_ARG); break;
			case '1': SETFLAG("1", FLAG_1, FLAG_1_ARG); break;
			case '2': SETFLAG("2", FLAG_2, FLAG_2_ARG); break;
			case '3': SETFLAG("3", FLAG_3, FLAG_3_ARG); break;
			case '4': SETFLAG("4", FLAG_4, FLAG_4_ARG); break;
			case '5': SETFLAG("5", FLAG_5, FLAG_5_ARG); break;
			case '6': SETFLAG("6", FLAG_6, FLAG_6_ARG); break;
			case '7': SETFLAG("7", FLAG_7, FLAG_7_ARG); break;
			case '8': SETFLAG("8", FLAG_8, FLAG_8_ARG); break;
			case '9': SETFLAG("9", FLAG_9, FLAG_9_ARG); break;
			case '@': SETFLAG("@", FLAG_AT, FLAG_AT_ARG); break;
			}
			++j;
			++i;
			break;
		default:
			goto retu_analysis;
		}
	}

	/*
	 * Column specific analysis
	 */
retu_analysis:
	if (flags&CMDARGS_R_NONE)
		goto argarg_analysis;

	for (; i < argc; i++, cmdargs.r_argc++) {
		/*
		 * Array expansion
		 */
		if (cmdargs.r_argc == r_argv_max - 1) {
			ARRAY_EXPANSION(r_argv_max,
				r_argv_max + r_argv_addition_size);
			r_argv_max += r_argv_addition_size;
		}

		switch (argv[i][0]) {
		case '0': 
		case '1': 
		case '2': 
		case '3': 
		case '4': 
		case '5': 
		case '6': 
		case '7': 
		case '8': 
		case '9': 
			/*
			 * Column number process
			 */
			p1 = &argv[i][0];	
			p2 = buf;
			while (isdigit(*p1)) {
				*p2++ = *p1++;
			}
			*p2 = '\0';
			cmdargs.r_argv[1+cmdargs.r_argc] = 
				(int)strtol(buf, (char **)NULL, 10);
			if (cmdargs.r_argv[1+cmdargs.r_argc] < mincol) {
				fprintf(stderr,
				        "%d must be 1 or over.\n",
				        cmdargs.r_argv[1+cmdargs.r_argc]);
				exit(EX_USAGE);
			}
			if (cmdargs.r_argv[1+cmdargs.r_argc] > 
				cmdargs.r_argv_max)
				cmdargs.r_argv_max = 
					cmdargs.r_argv[1+cmdargs.r_argc];

			/*
			 * Array expansion
			 */
			if (cmdargs.r_argv[1+cmdargs.r_argc] > 
				r_argv_max - 1) {
				ARRAY_EXPANSION(r_argv_max,
					r_argv_max +
					cmdargs.r_argv[1+cmdargs.r_argc])
				r_argv_max +=
					cmdargs.r_argv[1+cmdargs.r_argc];
			}
			cmdargs.r_index_exist
				[cmdargs.r_argv[1+cmdargs.r_argc]] = 
					R_INDEX_IS_EXISTENCE;
			cmdargs.r_index_to_argv[
				cmdargs.r_argv[1+cmdargs.r_argc]] = 
					1+cmdargs.r_argc;
			if (cmdargs.r_argv[1+cmdargs.r_argc] >
			    cmdargs.r_index_max)
				cmdargs.r_index_max =
					cmdargs.r_argv[1+cmdargs.r_argc];

			if ('\0' == *p1) {
				if (flags&CMDARGS_R_ARGARG_1_NEED)
					usage();
				continue;
			}

			/*
			 * Column range pre process
			 */
			delim = *p1++;
			range = 0;
			if ('/' == delim) {
				p2 = buf;
				if ('0' > *p1 || *p1 > '9') {
					fprintf(stderr, 
					        "The range must be "
						"a positive number.\n");
					exit(EX_USAGE);
				}
				while ('0' <= *p1 && *p1 <= '9') {
					*p2++ = *p1++;
				}
				*p2++ = '\0';
				range = (int)strtol(buf, (char **)NULL, 10);
				if (range < 1) {
					fprintf(stderr,
					        "%d must be 1 or over.\n",
				        	range);
					exit(EX_USAGE);
				}
				if (range > cmdargs.r_index_max)
					cmdargs.r_index_max = range;
				/*
				 * Array expansion
				 */
				k = cmdargs.r_argc+2;
				if (range > r_argv_max - 1) {
					ARRAY_EXPANSION(r_argv_max,
						range + 1)
					r_argv_max = range + 1;
				}

				if ('\0' == *p1)
					goto column_range_process;
				else
					delim = *p1++;
			}

			/*
			 * 1st argument process of the column number
			 */
			if (flags&CMDARGS_R_ARGARG_NONE)
				usage();
			cmdargs.r_argv_delim[1+cmdargs.r_argc] = delim;

			p2 = buf;
			if (single_delimiter_mode) {
				while ('\0' != *p1) {
					*p2++ = *p1++;
				}
			}
			else {
				while (delim != *p1 && '\0' != *p1) {
					*p2++ = *p1++;
				}
			}
			*p2++ = '\0';
			cmdargs.r_argv_arg1[1+cmdargs.r_argc] =
				calloc(1, p2 - buf);
			stpncpy(cmdargs.r_argv_arg1[
			                1+cmdargs.r_argc], buf, p2 - buf);

			/*
			 * 2nd argument process of the column number
			 */
			if (range && '\0' == *p1)
				goto column_range_process;

			if ('\0' == *p1) {
				if (flags&CMDARGS_R_ARGARG_2_NEED)
					usage();
				continue;
			}

			++p1;
			p2 = buf;
			if (double_delimiter_mode) {
				while ('\0' != *p1) {
					*p2++ = *p1++;
				}
			}
			else {
				while (delim != *p1 && '\0' != *p1) {
					*p2++ = *p1++;
				}
			}
			*p2++ = '\0';
			cmdargs.r_argv_arg2[1+cmdargs.r_argc] =
				calloc(1, p2 - buf);
			stpncpy(cmdargs.r_argv_arg2[
			                1+cmdargs.r_argc], buf, p2 - buf);

			/*
			 * 3rd argument process of the column number
			 */
			if (range && '\0' == *p1)
				goto column_range_process;

			if ('\0' == *p1) {
				if (flags&CMDARGS_R_ARGARG_3_NEED)
					usage();
				continue;
			}

			++p1;
			p2 = buf;
			while ('\0' != *p1) {
				*p2++ = *p1++;
			}
			*p2++ = '\0';
			cmdargs.r_argv_arg3[1+cmdargs.r_argc] =
				calloc(1, p2 - buf);
			stpncpy(cmdargs.r_argv_arg3[
			                1+cmdargs.r_argc], buf, p2 - buf);

			/*
			 * Column range pre process
			 */
column_range_process:
			/*
			 * Array expansion
			 */
			if (range) {
				if (cmdargs.r_argv[1+cmdargs.r_argc] <=
				            range) {
					j = cmdargs.r_argv[
						cmdargs.r_argc+1] + 1;
					if (cmdargs.r_argc >
					    r_argv_max - (range - j) - 2) {
						ARRAY_EXPANSION(r_argv_max,
							r_argv_max + 
							range - j + 
							r_argv_addition_size);
						r_argv_max += range - j +
							r_argv_addition_size;
					}
				}
				else {
					j = cmdargs.r_argv
						[cmdargs.r_argc+1] - 1;
					if (cmdargs.r_argc >
					    r_argv_max - (j - range) - 2) {
						ARRAY_EXPANSION(r_argv_max,
							r_argv_max + 
							j - range +
							r_argv_addition_size);
						r_argv_max += j - range +
							r_argv_addition_size;
					}
				}
			}
			if (range) {
				k = cmdargs.r_argc+2;
				if (cmdargs.r_argv[1+cmdargs.r_argc] <=
				            range) {
					j = cmdargs.r_argv[
						cmdargs.r_argc+1] + 1;
					while (j <= range) {
						cmdargs.r_argv[k] = j;
						cmdargs.r_argv_delim[k] =
							delim;
						cmdargs.r_argv_arg1[k] =
							cmdargs.r_argv_arg1
							[cmdargs.r_argc+1];
						cmdargs.r_argv_arg2[k] = 
							cmdargs.r_argv_arg2
							[cmdargs.r_argc+1];
						cmdargs.r_argv_arg3[k] = 
							cmdargs.r_argv_arg3
							[cmdargs.r_argc+1];
						cmdargs.r_index_exist[j] =
							R_INDEX_IS_EXISTENCE;
						cmdargs.r_index_to_argv
							[j] = k;
						++j;
						++k;
					}
					cmdargs.r_argc +=
					        range - cmdargs.r_argv[
						        cmdargs.r_argc+1]; 
				}
				else {
					j = cmdargs.r_argv
						[cmdargs.r_argc+1] - 1;
					for (; j >= range; j--, k++) {
						cmdargs.r_argv[k] = j;
						cmdargs.r_argv_delim[k] =
							delim;
						cmdargs.r_argv_arg1[k] =
							cmdargs.r_argv_arg1
							[cmdargs.r_argc+1];
						cmdargs.r_argv_arg2[k] = 
							cmdargs.r_argv_arg2
							[cmdargs.r_argc+1];
						cmdargs.r_argv_arg3[k] = 
							cmdargs.r_argv_arg3
							[cmdargs.r_argc+1];
						cmdargs.r_index_exist[j] =
							R_INDEX_IS_EXISTENCE;
						cmdargs.r_index_to_argv[j] =
							k;
					}
					cmdargs.r_argc +=
					        cmdargs.r_argv
							[cmdargs.r_argc+1]
							- range; 
				}
			}
			break;
		default:
			goto file_analysis;
		}
	}

argarg_analysis:
	if (!(flags&CMDARGS_A_NEED))
		goto file_analysis;

	for (; i < argc; i++, cmdargs.a_argc++) {
		if (cmdargs.a_argc > 0)
			REALLOC_SARRAY(cmdargs.a_argc+1,
				cmdargs.a_argc+2, cmdargs.a_argv)

		cmdargs.a_argv[cmdargs.a_argc+1] = argv[i];
	}
	if (NULL == cmdargs.a_argv[1]) {
		if (flags&CMDARGS_A_NEED && !FLAG_h && !FLAG_v)
			fprintf(stderr,
			    "You must specify at least an argument.\n\n");
			usage();
	}

	/*
	 * File specific analysis
	 */
file_analysis:
	if (flags&CMDARGS_R_NEED && 0 == cmdargs.r_argc)
		usage();

	if (flags&CMDARGS_F_NONE)
		goto str_to_ssvstring_process;

	for (; i < argc; i++, cmdargs.f_argc++) {
		if (cmdargs.f_argc > 0)
			REALLOC_SARRAY(cmdargs.f_argc+1,
				cmdargs.f_argc+2, cmdargs.f_argv)

		switch (argv[i][0]) {
		case '-':
			switch (argv[i][1]) {
			case '\0':
				if (stdin_file_used && \
				    !(flags&CMDARGS_STDIN_TO_TMPFILE)) {
					fprintf(stderr,
					    "You can specify the stdin " \
					    "only once.\n\n");
					usage();
				}
				cmdargs.f_argv[cmdargs.f_argc+1] = 
					STDIN_FILE;
				stdin_file_used = 1;
				continue;
				;;
			}
		default:
			cmdargs.f_argv[cmdargs.f_argc+1] = argv[i];
			break;
		}
	}
	if (NULL == cmdargs.f_argv[1]) {
		if (flags&CMDARGS_F_NEED && !FLAG_h && !FLAG_v) {
			fprintf(stderr,
			    "You must specify at least a file.\n\n");
			usage();
		}
		else if (stdin_file_used &&
		         !(flags&CMDARGS_STDIN_TO_TMPFILE)) {
			fprintf(stderr,
			    "You can specify the stdin only once.\n\n");
			usage();
		}
		cmdargs.f_argv[1] = STDIN_FILE;
		stdin_file_used = 1;
		++cmdargs.f_argc;
	}

	/*
	 * convert the arg string to the ssv string 
	 */
str_to_ssvstring_process:
	if (flags&CMDARGS_R_ARGARG_TO_SSVSTR) {
		char *ssvstr;
		int ssvstr_len = 10, arglen;
		ssvstr = calloc(1, ssvstr_len * sizeof(char));
#define R_ARGSTR_TO_SSVSTR(X) \
		if (NULL != X[i]) { \
			arglen = strlen(X[i]) + 1; \
			if (arglen * 2 - 1 > ssvstr_len) \
				ssvstr_len = arglen * 2 - 1; \
			ssvstr = calloc(1, ssvstr_len * sizeof(char)); \
			str2ssvstr(ssvstr, X[i]); \
			X[i] = ssvstr; \
		} 
		for (i = 1; i <= cmdargs.r_argc; i++) {
			R_ARGSTR_TO_SSVSTR(cmdargs.r_argv_arg1)
			R_ARGSTR_TO_SSVSTR(cmdargs.r_argv_arg2)
			R_ARGSTR_TO_SSVSTR(cmdargs.r_argv_arg3)
		}
	}

	/*
	 * Default options process
	 */
	if (FLAG_v)
		version();
	if (FLAG_h)
		usage();
	if ((FLAG_D && !stdin_file_used) || 
	    (FLAG_D && stdin_file_used &&
		!(flags&CMDARGS_STDIN_TO_TMPFILE)))
		printcmdargs();

	/*
	 * Convert the stdin to a temporality file
	 */
	if (stdin_file_used && flags&CMDARGS_STDIN_TO_TMPFILE) {
		stdintotempfile();
		if (FLAG_D)
			printcmdargs();
	}

	return 0;
}

int
getcmdargs_unlinktmpf(void)
{
	if (NULL == tempfile) 
		return 0;

	return (unlink(tempfile));
}

static void
stdintotempfile(void)
{
	FILE *fp_i, *fp_o;
	char b;

	mktempfile();
	fp_i = fopen(STDIN_FILE, "r");
	if (NULL == fp_i) \
		err(errno, "%s", STDIN_FILE); \
	fp_o = fopen(tempfile, "w");
	if (NULL == fp_o) \
		err(errno, "%s", tempfile); \

	while (EOF != (b = fgetc(fp_i)))
		fputc(b, fp_o);

	fclose(fp_o);
	fclose(fp_i);

	for (int i = 1; i <= cmdargs.f_argc; i++)
		if (STDIN_FILE == cmdargs.f_argv[i])
			cmdargs.f_argv[i] = tempfile;
}

static void
mktempfile(void)
{
	struct stat sb;
	int i, j, k, len;
	char *home = getenv("HOME"), *dir, *dir2;
	if (NULL == home || 0 == strcmp(home, "/"))
		home = "/tmp";

	len = strlen(home) + strlen(TMPDIR_NAME) + 2;
	dir = calloc(1, sizeof(char) * len);
	dir2 = calloc(1, sizeof(char) * len);
	sprintf(dir, "%s/%s", home, TMPDIR_NAME);

	/*
	 * Create a cache directory
	 */
	i = j = k = 0;
	while (1) {
		dir2[i] = dir[i];
		if ('/' == dir2[i] || '\0' == dir2[i]) {
			if (j == k) {
				if (0 != i && '/' == dir2[i])
					dir2[i] = '\0';
				if (-1 == stat(dir2, &sb))
					mkdir(dir2, S_IRWXU);
				if ('\0' == dir[i])
					break;
				k++;
				i = j = 0;
			}
			else {
				++i;
				++j;
			}
		}
		else
			++i;
	}

	/*
	 * Create a temporary file
	 */
	len += strlen(TMPFILE_NAME) + 1;
	tempfile = calloc(1, sizeof(char) * len);
	sprintf(tempfile, "%s/%s", dir, TMPFILE_NAME);

	if (-1 == mkstemp(tempfile))
		err(errno, "getcmdargs#mktempfile: %s: failed", tempfile);
}
