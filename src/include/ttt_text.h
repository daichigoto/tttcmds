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

#define ESC_SEQ_NORM	"\x1b[0m"
#define ESC_SEQ_BOLD	"\x1b[1m"
#define ESC_SEQ_GRAY	"\x1b[2m"
#define ESC_SEQ_UBAR	"\x1b[4m"

#define ES_BOLD(X)	ESC_SEQ_BOLD X ESC_SEQ_NORM
#define	ES_LIGHT(X)	ESC_SEQ_GRAY X ESC_SEQ_NORM
#define ES_UBAR(X)	ESC_SEQ_UBAR X ESC_SEQ_NORM

#define	ES_PROMPT1(X)	ESC_SEQ_BOLD "% " ESC_SEQ_NORM X "\n"
#define	ES_PROMPT2(X)	ESC_SEQ_BOLD "  " ESC_SEQ_NORM X "\n"

#define	ES_STDIN(X)	ESC_SEQ_GRAY X ESC_SEQ_NORM "\n"
#define	ES_STDOUT(X)	ESC_SEQ_GRAY X ESC_SEQ_NORM "\n"
#define	ES_STDERR(X)	ESC_SEQ_GRAY X ESC_SEQ_NORM "\n"

#define ES_CMD(X)	ES_BOLD(X)
#define ES_OPT(X)	ESC_SEQ_BOLD "-" X ESC_SEQ_NORM
#define ES_ARG(X)	ES_UBAR(X)
