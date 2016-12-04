# 
#  Copyright (c) 2016 Daichi GOTO
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

.include	"ttt.os.mk"
.include	"ttt.cmd.mk"
.include	"ttt.perm.mk"
.include	"ttt.dirs.mk"

CFLAGS=		-I. \
		-I${SRCINCDIR} \
		-L${LIBDIR} \
		-O2 \
		-pipe \
		-fno-omit-frame-pointer \
		-std=gnu99 \
		-Qunused-arguments \
		-fstack-protector \
		-Wsystem-headers \
		-Werror \
		-Wall \
		-Wno-format-y2k \
		-W \
		-Wno-unused-parameter \
		-Wstrict-prototypes \
		-Wmissing-prototypes \
		-Wpointer-arith \
		-Wreturn-type \
		-Wcast-qual \
		-Wwrite-strings \
		-Wswitch \
		-Wshadow \
		-Wunused-parameter \
		-Wcast-align \
		-Wchar-subscripts \
		-Winline \
		-Wnested-externs \
		-Wredundant-decls \
		-Wold-style-definition \
		-Wmissing-variable-declarations \
		-Wno-pointer-sign \
		-Wno-empty-body \
		-Wno-string-plus-int \
		-Wno-unused-const-variable \
		-Wno-incompatible-pointer-types-discards-qualifiers

.if ${OS} == "Linux"
CFLAGS+=	-Wno-system-headers \
		-lbsd \
		-ldb
.elif ${OS} == "Darwin"
CFLAGS+=	-Wno-system-headers
.endif

.if defined(DEBUG)
CFLAGS+=	-g -O0
.endif

.if !defined(OUT)
OUT!=		${BASENAME} $$(pwd)
.endif

.if !defined(OBJS)
OBJS!=		${LS} | ${GREP} '[.]c$$' 2> /dev/null | ${SED} 's/.c$$/.o/g'
.endif

OBJS?=		${OUT}.o
CORE?=		${OUT}.core
CLEANFILES?=	${OUT} ${BINDIR}/${OUT} ${OBJS} ${CORE} ${SLIB} ${DLIB}

# Directory operation
.if ${OBJS} == "" && !defined(TGTDIRS)
TGTDIRS!=	${FIND} . -type d | ${SED} 's,^[.][/]*,,'
.endif

.if defined(TGTDIRS)
build:
. for dir in ${TGTDIRS}
	cd ${dir}; ${MAKE}
. endfor

clean:
. for dir in ${TGTDIRS}
	cd ${dir}; ${MAKE} $@
. endfor
.endif

.SUFFIXES:	.o .c

# Library build
LIBVERSION?=	0
.if ${OS} == "Darwin"
DLIB?=		${LIBDIR}/${OUT}.${LIBVERSION}.dylib
LIBOBJS?=	${SRCDIR}/lib/libttt/*.o
.else
SLIB?=		${LIBDIR}/${OUT}.a
DLIB?=		${LIBDIR}/${OUT}.so.${LIBVERSION}
LIBOBJS?=	${LIBDIR}/libttt.a

.endif
.if ${OUT:Nlib*} == ""
.c.o:
	${CC} ${CFLAGS} -fPIC -c $< -o $@

${OUT}: ${OBJS}
.if exists(${SLIB})
	${RM} -f ${SLIB}
.endif
.if exists(${DLIB})
	${RM} -f ${DLIB}
.endif
	${CC} ${CFLAGS} -o ${DLIB} -shared ${OBJS}
	${CHMOD} ${LIBPERM} ${DLIB}
. if ${OS} != "Darwin"
	${AR} -crv ${SLIB} ${OBJS}
	${CHMOD} ${LIBPERM} ${SLIB}
. endif

.else

# Command build
.if exists(command.h) && exists(textsets.c)
build: ${OUT}

.c.o: command.h textsets.c
.else
.c.o: 
.endif
	${MAKE} prebuild 2> /dev/null || true
	${CC} ${CFLAGS} -c $< -o $@

ALIAS!=		${GREP} '^\#define ALIAS' command.h 2> /dev/null | \
		${SED} 's/[^"]*"\([^"]*\)"[^"]*/\1/'

. if ${ALIAS} != ""
CLEANFILES+=	${ALIAS:S,^,${BINDIR}/,}
. endif

${OUT}: ${OBJS}
.if exists(${BINDIR}/${OUT})
	${RM} -f ${BINDIR}/${OUT}
.endif
	${CC} ${CFLAGS} -o ${BINDIR}/${OUT} ${OBJS} ${LIBOBJS}
	${CHMOD} ${BINPERM} ${BINDIR}/${OUT}
. if ${OS} != "Darwin"
.  if !defined(DEBUG)
	${OBJCOPY} -S ${BINDIR}/${OUT}
.  endif
. endif
. if ${ALIAS} != ""
.  for i in ${ALIAS}
	${TEST} -L ${BINDIR}/${i} && ${RM} ${BINDIR}/${i} || ${TRUE}
	cd ${BINDIR}; ${LN} -s ${OUT} ${i}
.  endfor
. endif
.endif

# Clean operation
.if !target(clean)
clean:
	${RM} -f ${CLEANFILES}
.endif

.include	"ttt.install.mk"
.include	"ttt.test.mk"
