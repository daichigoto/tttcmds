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

#define _(X,Y,Z) settext(X,Y,Z)
#define _P(X) ES_PROMPT1(X)
#define _P2(X) ES_PROMPT2(X)
#define _S(X) ES_STDOUT(X)
#define _CMD(X) ES_CMD(X)
#define _OPT(X) ES_OPT(X)
#define _ARG(X) ES_ARG(X)
#define _ETC ES_UBAR("...")

#define R_ARGC cmdargs.r_argc
#define R_ARGV cmdargs.r_argv
#define R_ARGV_MAX cmdargs.r_argv_max
#define R_ARGV_ARG1 cmdargs.r_argv_arg1
#define R_ARGV_ARG2 cmdargs.r_argv_arg2
#define R_ARGV_ARG3 cmdargs.r_argv_arg3
#define R_ARGV_DELIM cmdargs.r_argv_delim
#define R_INDEX_EXIST cmdargs.r_index_exist
#define R_INDEX_TO_ARGV cmdargs.r_index_to_argv
#define R_INDEX_MAX cmdargs.r_index_max
#define R_INDEX_IS_EXISTENCE 1
#define R_INDEX_IS_NOT_EXISTENCE 0
#define R_INDEX_IS_NONE -1
#define F_ARGC cmdargs.f_argc
#define F_ARGV cmdargs.f_argv
#define A_ARGC cmdargs.a_argc
#define A_ARGV cmdargs.a_argv
#define FLAG_a cmdargs.flags[0]
#define FLAG_b cmdargs.flags[1]
#define FLAG_c cmdargs.flags[2]
#define FLAG_d cmdargs.flags[3]
#define FLAG_e cmdargs.flags[4]
#define FLAG_f cmdargs.flags[5]
#define FLAG_g cmdargs.flags[6]
#define FLAG_h cmdargs.flags[7]
#define FLAG_i cmdargs.flags[8]
#define FLAG_j cmdargs.flags[9]
#define FLAG_k cmdargs.flags[10]
#define FLAG_l cmdargs.flags[11]
#define FLAG_m cmdargs.flags[12]
#define FLAG_n cmdargs.flags[13]
#define FLAG_o cmdargs.flags[14]
#define FLAG_p cmdargs.flags[15]
#define FLAG_q cmdargs.flags[16]
#define FLAG_r cmdargs.flags[17]
#define FLAG_s cmdargs.flags[18]
#define FLAG_t cmdargs.flags[19]
#define FLAG_u cmdargs.flags[20]
#define FLAG_v cmdargs.flags[21]
#define FLAG_w cmdargs.flags[22]
#define FLAG_x cmdargs.flags[23]
#define FLAG_y cmdargs.flags[24]
#define FLAG_z cmdargs.flags[25]
#define FLAG_A cmdargs.flags[26]
#define FLAG_B cmdargs.flags[27]
#define FLAG_C cmdargs.flags[28]
#define FLAG_D cmdargs.flags[29]
#define FLAG_E cmdargs.flags[30]
#define FLAG_F cmdargs.flags[31]
#define FLAG_G cmdargs.flags[32]
#define FLAG_H cmdargs.flags[33]
#define FLAG_I cmdargs.flags[34]
#define FLAG_J cmdargs.flags[35]
#define FLAG_K cmdargs.flags[36]
#define FLAG_L cmdargs.flags[37]
#define FLAG_M cmdargs.flags[38]
#define FLAG_N cmdargs.flags[39]
#define FLAG_O cmdargs.flags[40]
#define FLAG_P cmdargs.flags[41]
#define FLAG_Q cmdargs.flags[42]
#define FLAG_R cmdargs.flags[43]
#define FLAG_S cmdargs.flags[44]
#define FLAG_T cmdargs.flags[45]
#define FLAG_U cmdargs.flags[46]
#define FLAG_V cmdargs.flags[47]
#define FLAG_W cmdargs.flags[48]
#define FLAG_X cmdargs.flags[49]
#define FLAG_Y cmdargs.flags[50]
#define FLAG_Z cmdargs.flags[51]
#define FLAG_0 cmdargs.flags[52]
#define FLAG_1 cmdargs.flags[53]
#define FLAG_2 cmdargs.flags[54]
#define FLAG_3 cmdargs.flags[55]
#define FLAG_4 cmdargs.flags[56]
#define FLAG_5 cmdargs.flags[57]
#define FLAG_6 cmdargs.flags[58]
#define FLAG_7 cmdargs.flags[59]
#define FLAG_8 cmdargs.flags[60]
#define FLAG_9 cmdargs.flags[61]
#define FLAG_AT cmdargs.flags[62]
#define FLAG_a_ARG cmdargs.flags_arg[0]
#define FLAG_b_ARG cmdargs.flags_arg[1]
#define FLAG_c_ARG cmdargs.flags_arg[2]
#define FLAG_d_ARG cmdargs.flags_arg[3]
#define FLAG_e_ARG cmdargs.flags_arg[4]
#define FLAG_f_ARG cmdargs.flags_arg[5]
#define FLAG_g_ARG cmdargs.flags_arg[6]
#define FLAG_h_ARG cmdargs.flags_arg[7]
#define FLAG_i_ARG cmdargs.flags_arg[8]
#define FLAG_j_ARG cmdargs.flags_arg[9]
#define FLAG_k_ARG cmdargs.flags_arg[10]
#define FLAG_l_ARG cmdargs.flags_arg[11]
#define FLAG_m_ARG cmdargs.flags_arg[12]
#define FLAG_n_ARG cmdargs.flags_arg[13]
#define FLAG_o_ARG cmdargs.flags_arg[14]
#define FLAG_p_ARG cmdargs.flags_arg[15]
#define FLAG_q_ARG cmdargs.flags_arg[16]
#define FLAG_r_ARG cmdargs.flags_arg[17]
#define FLAG_s_ARG cmdargs.flags_arg[18]
#define FLAG_t_ARG cmdargs.flags_arg[19]
#define FLAG_u_ARG cmdargs.flags_arg[20]
#define FLAG_v_ARG cmdargs.flags_arg[21]
#define FLAG_w_ARG cmdargs.flags_arg[22]
#define FLAG_x_ARG cmdargs.flags_arg[23]
#define FLAG_y_ARG cmdargs.flags_arg[24]
#define FLAG_z_ARG cmdargs.flags_arg[25]
#define FLAG_A_ARG cmdargs.flags_arg[26]
#define FLAG_B_ARG cmdargs.flags_arg[27]
#define FLAG_C_ARG cmdargs.flags_arg[28]
#define FLAG_D_ARG cmdargs.flags_arg[29]
#define FLAG_E_ARG cmdargs.flags_arg[30]
#define FLAG_F_ARG cmdargs.flags_arg[31]
#define FLAG_G_ARG cmdargs.flags_arg[32]
#define FLAG_H_ARG cmdargs.flags_arg[33]
#define FLAG_I_ARG cmdargs.flags_arg[34]
#define FLAG_J_ARG cmdargs.flags_arg[35]
#define FLAG_K_ARG cmdargs.flags_arg[36]
#define FLAG_L_ARG cmdargs.flags_arg[37]
#define FLAG_M_ARG cmdargs.flags_arg[38]
#define FLAG_N_ARG cmdargs.flags_arg[39]
#define FLAG_O_ARG cmdargs.flags_arg[40]
#define FLAG_P_ARG cmdargs.flags_arg[41]
#define FLAG_Q_ARG cmdargs.flags_arg[42]
#define FLAG_R_ARG cmdargs.flags_arg[43]
#define FLAG_S_ARG cmdargs.flags_arg[44]
#define FLAG_T_ARG cmdargs.flags_arg[45]
#define FLAG_U_ARG cmdargs.flags_arg[46]
#define FLAG_V_ARG cmdargs.flags_arg[47]
#define FLAG_W_ARG cmdargs.flags_arg[48]
#define FLAG_X_ARG cmdargs.flags_arg[49]
#define FLAG_Y_ARG cmdargs.flags_arg[50]
#define FLAG_Z_ARG cmdargs.flags_arg[51]
#define FLAG_0_ARG cmdargs.flags_arg[52]
#define FLAG_1_ARG cmdargs.flags_arg[53]
#define FLAG_2_ARG cmdargs.flags_arg[54]
#define FLAG_3_ARG cmdargs.flags_arg[55]
#define FLAG_4_ARG cmdargs.flags_arg[56]
#define FLAG_5_ARG cmdargs.flags_arg[57]
#define FLAG_6_ARG cmdargs.flags_arg[58]
#define FLAG_7_ARG cmdargs.flags_arg[59]
#define FLAG_8_ARG cmdargs.flags_arg[60]
#define FLAG_9_ARG cmdargs.flags_arg[61]
#define FLAG_AT_ARG cmdargs.flags_arg[62]
