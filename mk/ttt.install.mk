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

.include	"ttt.os.mk"

CMDS!=		${LS} -F ${BINDIR} | ${GREP} -v '^[.]' | \
		${GREP} -v '@$$' | ${SED} 's/*$$//'
LNKS!=		${LS} -l ${BINDIR} | ${GREP} -v '^[.]' | \
		${GREP} -- '->' | \
		${SED} 's/^.* \([^ ][^ ]*\) -> \([^ ][^ ]*\)/\2:\1/'
LIBS!=		${LS} ${LIBDIR} | ${GREP} -v '^[.]'
INCS!=		${LS} ${INCLUDEDIR} | ${GREP} -v '^[.]'

.if defined(STAGEDIR)
INSTALL_OWNER!=	id -u
INSTALL_GROUP!=	id -g
.else
INSTALL_OWNER?=	root
. if ${OS} == "Linux"
INSTALL_GROUP?=	root
. else
INSTALL_GROUP?=	wheel
. endif
.endif

install:
.for i in ${CMDS}
	${INSTALL} -o ${INSTALL_OWNER} -g ${INSTALL_GROUP} \
		-m ${BINPERM} ${BINDIR}/${i} ${INSTALL_BINDIR}/${i}
.endfor
.for i in ${LNKS}
	cd ${INSTALL_BINDIR}; \
	${LN} -s $$(${ECHO} ${i} | ${SED} 's/:/ /')
.endfor
.for i in ${LIBS}
	${INSTALL} -o ${INSTALL_OWNER} -g ${INSTALL_GROUP} \
		-m ${LIBPERM} ${LIBDIR}/${i} ${INSTALL_LIBDIR}/${i}
	case ${i} in \
	*.so.[0-9]*) \
		cd ${INSTALL_LIBDIR}; \
		${LN} -s ${i} $$(${ECHO} ${i} | ${SED} 's/[.][0-9][0-9.]*//') \
		;; \
	esac
.endfor
.for i in ${INCS}
	${INSTALL} -o ${INSTALL_OWNER} -g ${INSTALL_GROUP} \
		-m ${INCLUDEPERM} \
		${INCLUDEDIR}/${i} ${INSTALL_INCLUDEDIR}/${i}
.endfor

uninstall:
.for i in ${CMDS}
	${RM} -f ${INSTALL_BINDIR}/${i}
.endfor
.for i in ${LNKS}
	${RM} -f ${INSTALL_BINDIR}/$$(${ECHO} ${i} | \
		${CUT} -d: -f2)
.endfor
.for i in ${LIBS}
	${RM} -f ${INSTALL_LIBDIR}/${i}
.endfor
.for i in ${INCS}
	${RM} -f ${INSTALL_INCLUDEDIR}/${i}
.endfor
