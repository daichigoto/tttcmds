#  Copyright (c) 2021 Daichi GOTO
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

ifndef TOPDIR
decisionpath=$(CURDIR)/mk/ttt.build.mk
  ifeq ($(wildcard $(decisionpath)),$(decisionpath))
TOPDIR=		$(CURDIR)
  endif

decisionpath=$(CURDIR)/../mk/ttt.build.mk
 ifeq ($(wildcard $(decisionpath)),$(decisionpath))
TOPDIR=		$(shell echo $(CURDIR) | sed 's,/[^/]*$$,/,')
 endif

decisionpath=$(CURDIR)/../../mk/ttt.build.mk
 ifeq ($(wildcard $(decisionpath)),$(decisionpath))
TOPDIR=		$(shell echo $(CURDIR) | sed 's,/[^/]*/[^/]*$$,/,')
 endif

decisionpath=$(CURDIR)/../../../mk/ttt.build.mk
 ifeq ($(wildcard $(decisionpath)),$(decisionpath))
TOPDIR=		$(shell echo $(CURDIR) | sed 's,/[^/]*/[^/]*/[^/]*$$,/,')
 endif
endif

include		$(TOPDIR)/ttt.win.dirs.mk

#			TARGET	build	clean	test	report
# tttcmd/			OK	OK	OK	OK
#	bin/			-	-	-	-
#	include/		-	-	-	-
#	lib/			-	-	-	-
#	mk/			-	-	-	-
#	src/			OK	OK	OK	-
#		bin/		OK	OK	OK	-
#			cmd/	OK	OK	OK	-
#		contrib/	-	-	-	-
#		include/	OK	OK	-	-
#		lib/		OK	OK	-	-
#			libttt/	OK	OK	-	-
#	tests/			OK	OK	OK	OK
#		bin/		OK	OK	OK	OK
#			cmd/	OK	OK	OK	OK
#
# all: build

ifeq ($(WORKPLACE),/src/bin)
endif

# # /src/bin/cmds
# .elif ${WORKPLACE:C,/[^/]*$,,} == "/src/bin"
# . if !defined(OBJS)
# OBJS!=		${LS} | ${GREP} '[.]c$$' 2> /dev/null | ${SED} 's/.c$$/.o/g'
# . endif
# CLEANFILES?=	${DIRNAME} ${BINDIR}/${DIRNAME} ${OBJS} ${DIRNAME}.core
# LIBOBJS?=	${SRCDIR}/lib/libttt/*.o
# ALIAS!=		${GREP} '^\#define ALIAS' command.h 2> /dev/null | \
# 		${SED} 's/[^"]*"\([^"]*\)"[^"]*/\1/'
# . if ${ALIAS} != ""
# CLEANFILES+=	${ALIAS:S,^,${BINDIR}/,}
# . endif
# . if !target(build)
# all:	build
# build: ${DIRNAME}
# . endif
# ${DIRNAME}: ${OBJS}
# 	${RM} -f ${BINDIR}/${DIRNAME}
# 	${CC} ${CFLAGS} -o ${BINDIR}/${DIRNAME} ${OBJS} ${LIBOBJS}
# . if ${OS} != "Darwin"
# .  if !defined(WITH_DEBUG)
# 	${OBJCOPY} -S ${BINDIR}/${DIRNAME}
# .  endif
# . endif
# 	${CHMOD} ${BINPERM} ${BINDIR}/${DIRNAME}
# . if ${ALIAS} != ""
# .  for i in ${ALIAS}
# 	${TEST} -L ${BINDIR}/${i} && ${RM} ${BINDIR}/${i} || ${TRUE}
# 	cd ${BINDIR}; ${LN} -s ${DIRNAME} ${i}
# .  endfor
# . endif
# . if exists(command.h)
# .c.o: command.h textsets.c
# 	${MAKE} prebuild 2> /dev/null || ${TRUE}
# 	${CC} ${CFLAGS} -c $< -o $@
# . else
# .c.o:
# 	${MAKE} prebuild 2> /dev/null || ${TRUE}
# 	${CC} ${CFLAGS} -c $< -o $@
# . endif
# . if !target(clean)
# clean:
# 	${RM} -f ${CLEANFILES}
# . endif
# test: build
# . if exists(${TESTDIR}/${WORKPLACE:C,^/src/,,})
# 	cd ${TESTDIR}/${WORKPLACE:C,^/src/,,}; ${MAKE} $@
# . endif

ifeq ($(WORKPLACE),/src/lib)
endif

ifeq ($(WORKPLACE),/src/include)
# OBJS!=		${LS} | ${GREP} '[.]h$$' 2> /dev/null
# all:	build
# build:
# .for i in ${OBJS}
# 	${CP} ${i} ${INCLUDEDIR}/${i}
# 	${CHMOD} ${INCLUDEPERM} ${INCLUDEDIR}/${i}
# .endfor
# clean:
# .for i in ${OBJS}
# 	${RM} -f ${INCLUDEDIR}/${i}
# .endfor
endif

# # /src/lib/libttt
# .elif ${WORKPLACE} == "/src/lib/libttt"
# OBJS!=		${LS} | ${GREP} '[.]c$$' 2> /dev/null | ${SED} 's/.c$$/.o/g'
# . if ${OS} == "Darwin"
# DLIB?=		${LIBDIR}/${DIRNAME}.${LIBVERSION}.dylib
# LIBOBJS?=	${SRCDIR}/lib/${DIRNAME}/*.o
# . else
# SLIB?=		${LIBDIR}/${DIRNAME}.a
# DLIB?=		${LIBDIR}/${DIRNAME}.so.${LIBVERSION}
# LIBOBJS?=	${SRCDIR}/lib/${DIRNAME}/*.o
# . endif
# all:	build
# build: ${OBJS}
# 	${RM} -f ${SLIB} ${DLIB}
# . if ${OS} == "FreeBSD"
# 	${CC} ${CFLAGS} -o ${DLIB} -shared ${OBJS} \
# 		-Wl,-soname=${DIRNAME}.so.${LIBVERSION:C/[.][0-9][0-9]*[.][0-9][0-9]*$$//}
# .  if !defined(WITH_DEBUG)
# 	${OBJCOPY} -S ${DLIB}
# .  endif
# . elif ${OS} == "Darwin"
# 	${CC} ${CFLAGS} -o ${DLIB} -shared ${OBJS} -Wl
# . endif
# 	${CHMOD} ${LIBPERM} ${DLIB}
# . if ${OS} != "Darwin"
# 	${AR} -crv ${SLIB} ${OBJS}
# 	${CHMOD} ${LIBPERM} ${SLIB}
# . endif
# .c.o:
# 	${CC} ${CFLAGS} -fPIC -c $< -o $@
# clean:
# 	${RM} -f ${DLIB} ${SLIB} ${LIBOBJS}

# # /tests
# .elif ${WORKPLACE} == "/tests"
# TARGETDIRS!=	${FIND} . -type d -maxdepth 1 | ${SED} 's,^[.][/]*,,'
# test:
# 	${ENV} PATH="${BINDIR}:${PATH}" ${KYUA} $@
# all:	build
# build:
# 	cd ${SRCDIR}; ${MAKE} $@
# clean: 
# 	cd ${SRCDIR}; ${MAKE} $@
# report:
# 	${KYUA} report-html

# # /tests/bin
# .elif ${WORKPLACE} == "/tests/bin"
# TARGETDIRS!=	${FIND} . -type d -maxdepth 1 | ${SED} 's,^[.][/]*,,'
# test: 
# 	${ENV} PATH="${BINDIR}:${PATH}" ${KYUA} $@
# all:	build
# build:
# 	cd ${SRCDIR}/bin; ${MAKE} $@
# clean:
# 	cd ${SRCDIR}/bin; ${MAKE} $@
# 	${MAKE} clean-foreachdir
# report:
# 	${KYUA} report-html

# # /tests/bin/cmds
# .elif ${WORKPLACE:C,/[^/]*$,,} == "/tests/bin"
# test:
# 	${MAKE} build
# 	${ENV} PATH="${BINDIR}:${PATH}" ${KYUA} $@
# all:	build
# build:
# 	cd ${SRCDIR}/${WORKPLACE:C,^/tests/,,}; ${MAKE} $@
# clean:
# 	cd ${SRCDIR}/${WORKPLACE:C,^/tests/,,}; ${MAKE} $@
# 	${RM} -rf html
# report: 
# 	${MAKE} clean build
# 	${KYUA} report-html
# .endif

# build-foreachdir:
# .for dir in ${TARGETDIRS}
# 	( cd ${dir}; ${MAKE} build )
# .endfor

# clean-foreachdir:
# .for dir in ${TARGETDIRS}
# 	( cd ${dir}; ${MAKE} clean )
# .endfor

# .include	"ttt.install.mk"
