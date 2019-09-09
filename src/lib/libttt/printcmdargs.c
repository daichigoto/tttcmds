/*
 * Copyright (c) 2016 Daichi GOTO
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

void
printcmdargs(void)
{
	/*
	 * Command name
	 */
	fprintf(stderr,"CMDNAME\t\t%s\n", cmdargs.cmdname);

	/*
	 * Options and options arguments
	 */
	if (FLAG_a) fprintf(stderr,"FLAG_a\t\tFLAG_a_ARG %s\n", FLAG_a_ARG);
	if (FLAG_b) fprintf(stderr,"FLAG_b\t\tFLAG_b_ARG %s\n", FLAG_b_ARG);
	if (FLAG_c) fprintf(stderr,"FLAG_c\t\tFLAG_c_ARG %s\n", FLAG_c_ARG);
	if (FLAG_d) fprintf(stderr,"FLAG_d\t\tFLAG_d_ARG %s\n", FLAG_d_ARG);
	if (FLAG_e) fprintf(stderr,"FLAG_e\t\tFLAG_e_ARG %s\n", FLAG_e_ARG);
	if (FLAG_f) fprintf(stderr,"FLAG_f\t\tFLAG_f_ARG %s\n", FLAG_f_ARG);
	if (FLAG_g) fprintf(stderr,"FLAG_g\t\tFLAG_g_ARG %s\n", FLAG_g_ARG);
	if (FLAG_h) fprintf(stderr,"FLAG_h\t\tFLAG_h_ARG %s\n", FLAG_h_ARG);
	if (FLAG_i) fprintf(stderr,"FLAG_i\t\tFLAG_i_ARG %s\n", FLAG_i_ARG);
	if (FLAG_j) fprintf(stderr,"FLAG_j\t\tFLAG_j_ARG %s\n", FLAG_j_ARG);
	if (FLAG_k) fprintf(stderr,"FLAG_k\t\tFLAG_k_ARG %s\n", FLAG_k_ARG);
	if (FLAG_l) fprintf(stderr,"FLAG_l\t\tFLAG_l_ARG %s\n", FLAG_l_ARG);
	if (FLAG_m) fprintf(stderr,"FLAG_m\t\tFLAG_m_ARG %s\n", FLAG_m_ARG);
	if (FLAG_n) fprintf(stderr,"FLAG_n\t\tFLAG_n_ARG %s\n", FLAG_n_ARG);
	if (FLAG_o) fprintf(stderr,"FLAG_o\t\tFLAG_o_ARG %s\n", FLAG_o_ARG);
	if (FLAG_p) fprintf(stderr,"FLAG_p\t\tFLAG_p_ARG %s\n", FLAG_p_ARG);
	if (FLAG_q) fprintf(stderr,"FLAG_q\t\tFLAG_q_ARG %s\n", FLAG_q_ARG);
	if (FLAG_r) fprintf(stderr,"FLAG_r\t\tFLAG_r_ARG %s\n", FLAG_r_ARG);
	if (FLAG_s) fprintf(stderr,"FLAG_s\t\tFLAG_s_ARG %s\n", FLAG_s_ARG);
	if (FLAG_t) fprintf(stderr,"FLAG_t\t\tFLAG_t_ARG %s\n", FLAG_t_ARG);
	if (FLAG_u) fprintf(stderr,"FLAG_u\t\tFLAG_u_ARG %s\n", FLAG_u_ARG);
	if (FLAG_v) fprintf(stderr,"FLAG_v\t\tFLAG_v_ARG %s\n", FLAG_v_ARG);
	if (FLAG_w) fprintf(stderr,"FLAG_w\t\tFLAG_w_ARG %s\n", FLAG_w_ARG);
	if (FLAG_x) fprintf(stderr,"FLAG_x\t\tFLAG_x_ARG %s\n", FLAG_x_ARG);
	if (FLAG_y) fprintf(stderr,"FLAG_y\t\tFLAG_y_ARG %s\n", FLAG_y_ARG);
	if (FLAG_z) fprintf(stderr,"FLAG_z\t\tFLAG_z_ARG %s\n", FLAG_z_ARG);
                                                             
	if (FLAG_A) fprintf(stderr,"FLAG_A\t\tFLAG_A_ARG %s\n", FLAG_A_ARG);
	if (FLAG_B) fprintf(stderr,"FLAG_B\t\tFLAG_B_ARG %s\n", FLAG_B_ARG);
	if (FLAG_C) fprintf(stderr,"FLAG_C\t\tFLAG_C_ARG %s\n", FLAG_C_ARG);
	if (FLAG_D) fprintf(stderr,"FLAG_D\t\tFLAG_D_ARG %s\n", FLAG_D_ARG);
	if (FLAG_E) fprintf(stderr,"FLAG_E\t\tFLAG_E_ARG %s\n", FLAG_E_ARG);
	if (FLAG_F) fprintf(stderr,"FLAG_F\t\tFLAG_F_ARG %s\n", FLAG_F_ARG);
	if (FLAG_G) fprintf(stderr,"FLAG_G\t\tFLAG_G_ARG %s\n", FLAG_G_ARG);
	if (FLAG_H) fprintf(stderr,"FLAG_H\t\tFLAG_H_ARG %s\n", FLAG_H_ARG);
	if (FLAG_I) fprintf(stderr,"FLAG_I\t\tFLAG_I_ARG %s\n", FLAG_I_ARG);
	if (FLAG_J) fprintf(stderr,"FLAG_J\t\tFLAG_J_ARG %s\n", FLAG_J_ARG);
	if (FLAG_K) fprintf(stderr,"FLAG_K\t\tFLAG_K_ARG %s\n", FLAG_K_ARG);
	if (FLAG_L) fprintf(stderr,"FLAG_L\t\tFLAG_L_ARG %s\n", FLAG_L_ARG);
	if (FLAG_M) fprintf(stderr,"FLAG_M\t\tFLAG_M_ARG %s\n", FLAG_M_ARG);
	if (FLAG_N) fprintf(stderr,"FLAG_N\t\tFLAG_N_ARG %s\n", FLAG_N_ARG);
	if (FLAG_O) fprintf(stderr,"FLAG_O\t\tFLAG_O_ARG %s\n", FLAG_O_ARG);
	if (FLAG_P) fprintf(stderr,"FLAG_P\t\tFLAG_P_ARG %s\n", FLAG_P_ARG);
	if (FLAG_Q) fprintf(stderr,"FLAG_Q\t\tFLAG_Q_ARG %s\n", FLAG_Q_ARG);
	if (FLAG_R) fprintf(stderr,"FLAG_R\t\tFLAG_R_ARG %s\n", FLAG_R_ARG);
	if (FLAG_S) fprintf(stderr,"FLAG_S\t\tFLAG_S_ARG %s\n", FLAG_S_ARG);
	if (FLAG_T) fprintf(stderr,"FLAG_T\t\tFLAG_T_ARG %s\n", FLAG_T_ARG);
	if (FLAG_U) fprintf(stderr,"FLAG_U\t\tFLAG_U_ARG %s\n", FLAG_U_ARG);
	if (FLAG_V) fprintf(stderr,"FLAG_V\t\tFLAG_V_ARG %s\n", FLAG_V_ARG);
	if (FLAG_W) fprintf(stderr,"FLAG_W\t\tFLAG_W_ARG %s\n", FLAG_W_ARG);
	if (FLAG_X) fprintf(stderr,"FLAG_X\t\tFLAG_X_ARG %s\n", FLAG_X_ARG);
	if (FLAG_Y) fprintf(stderr,"FLAG_Y\t\tFLAG_Y_ARG %s\n", FLAG_Y_ARG);
	if (FLAG_Z) fprintf(stderr,"FLAG_Z\t\tFLAG_Z_ARG %s\n", FLAG_Z_ARG);
                                            
	if (FLAG_0) fprintf(stderr,"FLAG_0\t\tFLAG_0_ARG %s\n", FLAG_0_ARG);
	if (FLAG_1) fprintf(stderr,"FLAG_1\t\tFLAG_1_ARG %s\n", FLAG_1_ARG);
	if (FLAG_2) fprintf(stderr,"FLAG_2\t\tFLAG_2_ARG %s\n", FLAG_2_ARG);
	if (FLAG_3) fprintf(stderr,"FLAG_3\t\tFLAG_3_ARG %s\n", FLAG_3_ARG);
	if (FLAG_4) fprintf(stderr,"FLAG_4\t\tFLAG_4_ARG %s\n", FLAG_4_ARG);
	if (FLAG_5) fprintf(stderr,"FLAG_5\t\tFLAG_5_ARG %s\n", FLAG_5_ARG);
	if (FLAG_6) fprintf(stderr,"FLAG_6\t\tFLAG_6_ARG %s\n", FLAG_6_ARG);
	if (FLAG_7) fprintf(stderr,"FLAG_7\t\tFLAG_7_ARG %s\n", FLAG_7_ARG);
	if (FLAG_8) fprintf(stderr,"FLAG_8\t\tFLAG_8_ARG %s\n", FLAG_8_ARG);
	if (FLAG_9) fprintf(stderr,"FLAG_9\t\tFLAG_9_ARG %s\n", FLAG_9_ARG);

	if (FLAG_AT) fprintf(stderr,"atflag\t\tatflag_arg %s\n", FLAG_AT_ARG);

	/*
	 * File specifics
	 */
	fprintf(stderr,"\n");
	fprintf(stderr,"F_ARGC\t\t%d\n", F_ARGC);
	int i;
	for (i = 1; i <= F_ARGC; i++)  
		fprintf(stderr,"F_ARGV[%d]\t%s\n", i, F_ARGV[i]);

	/*
	 * Column specifics
	 */
	fprintf(stderr,"\n");
	fprintf(stderr,"R_ARGC\t\t%d\n", R_ARGC);
	fprintf(stderr,"R_ARGV_MAX\t%d\n", R_ARGV_MAX);

	for (i = 0; NULL != R_ARGV && i <= R_ARGC; i++)
		fprintf(stderr,"R_ARGV[%d]\t%d\n", i, R_ARGV[i]);

	if (NULL != R_ARGV_ARG1) {
		putchar('\n');
		for (i = 0; i <= R_INDEX_MAX; i++)
			fprintf(stderr,"R_ARGV_ARG1[%d]\t%s\n",
				i, R_ARGV_ARG1[i]);
	}

	if (NULL != R_ARGV_ARG2) {
		putchar('\n');
		for (i = 0; i <= R_INDEX_MAX; i++)
			fprintf(stderr,"R_ARGV_ARG2[%d]\t%s\n",
				i, R_ARGV_ARG2[i]);
	}

	if (NULL != R_ARGV_ARG3) {
		putchar('\n');
		for (i = 0; i <= R_INDEX_MAX; i++)
			fprintf(stderr,"R_ARGV_ARG3[%d]\t%s\n",
				i, R_ARGV_ARG3[i]);
	}

	if (NULL != R_ARGV_DELIM) {
		putchar('\n');
		for (i = 0; i <= R_INDEX_MAX; i++)
			if ('\0' == R_ARGV_DELIM[i])
				fprintf(stderr,"R_ARGV_DELIM[%d]\t\\0\n",
					i);
			else
				fprintf(stderr,"R_ARGV_DELIM[%d]\t%c\n",
					i, R_ARGV_DELIM[i]);
	}

	fprintf(stderr,"\nR_INDEX_MAX\t\t%d\n", R_INDEX_MAX);

	if (NULL != R_INDEX_TO_ARGV) {
		for (i = 0; i <= R_INDEX_MAX; i++)
			fprintf(stderr,"R_INDEX_TO_ARGV[%d]\t%d\n", i,
				R_INDEX_TO_ARGV[i]);
	}

	if (NULL != R_INDEX_EXIST) {
		fprintf(stderr,"\n");
		for (i = 0; i <= R_INDEX_MAX; i++)
			fprintf(stderr,"R_INDEX_EXIST[%d]\t%d\n", i,
				R_INDEX_EXIST[i]);
	}

	fprintf(stderr,"\n");
}
