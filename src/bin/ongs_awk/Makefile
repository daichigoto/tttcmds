#
#  Copyright (c) 2016,2018 Daichi GOTO
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modifigation, are permitted provided that the following conditions are
#  met:
#
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

.include	"../../../mk/ttt.os.mk"
.include	"../../../mk/ttt.cmd.mk"
.include	"../../../mk/ttt.dirs.mk"
.include	"../../../mk/ttt.perm.mk"

AWKSRC=		${.CURDIR}/../../contrib/one-true-awk
.PATH:		${AWKSRC}

OUT=		ongs_awk
ALIAS=		owk

SRC=		awkgram.c awkgram.h ytab.h maketab proctab.c
OBJS=		b.o lex.o lib.o main.o parse.o run.o tran.o \
		awkgram.o proctab.o

CFLAGS=		-I. \
		-I${AWKSRC} \
		-lm \
		-O2 \
		-pipe \
		-DHAS_ISBLANK \
		-DFOPEN_MAX=64 \
		-g
.if ${COMPILER_TYPE} == "clang"
CFLAGS+=	-std=gnu99 \
		-Wsystem-headers \
		-Werror \
		-Wno-pointer-sign \
		-Wno-empty-body \
		-Wno-string-plus-int \
		-Wno-unused-const-variable \
		-Wno-tautological-compare \
		-Wno-unused-value \
		-Wno-parentheses-equality \
		-Wno-unused-function \
		-Wno-enum-conversion \
		-Wno-switch \
		-Wno-switch-enum \
		-Wno-knr-promoted-parameter \
		-Wno-parentheses \
		-Qunused-arguments
.endif
.if ${OS} == "Linux"
CFLAGS+=	-Wno-typedef-redefinition \
		-Wno-gnu-designator \
		-Wno-builtin-requires-header 
.elif ${OS} == "Darwin"
CFLAGS+=	-Wno-nullability-completeness \
		-Wno-macro-redefined \
		-Wno-typedef-redefinition
.endif

# XXX
# The following option has been removed to build with FreeBSD 10.*. 
# I should undo it once FreeBSD 10.* support is finished.
#
#		-fstack-protector-strong \
#		-Wno-unused-local-typedef \

FUNCS=		b lex lib main parse run tran

build:
	${YACC} -d -o awkgram.c ${AWKSRC}/awkgram.y
	${LN} -sf awkgram.h ytab.h
	${CC} ${CFLAGS} ${AWKSRC}/maketab.c -o maketab
	./maketab > proctab.c
	${CC} ${CFLAGS} -c awkgram.c -o awkgram.o
	${CC} ${CFLAGS} -c proctab.c -o proctab.o
.for i in ${FUNCS}
	${CC} ${CFLAGS} -I${AWKSRC} -c ${AWKSRC}/${i}.c -o ${i}.o
.endfor
.if exists(${BINDIR}/${OUT})
	${RM} -f ${BINDIR}/${OUT}
.endif
	${CC} ${CFLAGS} -o ${BINDIR}/${OUT} \
		awkgram.o b.o lex.o lib.o main.o parse.o proctab.o \
		run.o tran.o \
		${SRCDIR}/lib/libttt/ssvstr2str.o \
		${SRCDIR}/lib/libttt/str2ssvstr.o \
		-lm
	${CHMOD} ${BINPERM} ${BINDIR}/${OUT}
.if ${OS} != "Darwin"
	${OBJCOPY} -S ${BINDIR}/${OUT}
.endif
.for i in ${ALIAS}
	${TEST} -L ${BINDIR}/${i} && ${RM} ${BINDIR}/${i} || ${TRUE}
	cd ${BINDIR}; ${LN} -s ${OUT} ${i}
.endfor
.if ${OS} == "Darwin"
	${RM} -rf maketab.dSYM
.endif

clean:
	${RM} -f ${BINDIR}/${OUT} ${SRC} ${OBJS} 
.for i in ${ALIAS}
	${RM} -f ${BINDIR}/${i}
.endfor
