# 
#  Copyright (c) 2016,2017,2018 Daichi GOTO
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

.if !defined(TOPDIR)
. if exists(${.CURDIR}/mk/ttt.build.mk)
TOPDIR=		${.CURDIR}
. elif exists(${.CURDIR}/../mk/ttt.build.mk)
TOPDIR=		${.CURDIR:C,/[^/]*$,,}
. elif exists(${.CURDIR}/../../mk/ttt.build.mk)
TOPDIR=		${.CURDIR:C,/[^/]*/[^/]*$,,}
. elif exists(${.CURDIR}/../../../mk/ttt.build.mk)
TOPDIR=		${.CURDIR:C,/[^/]*/[^/]*/[^/]*$,,}
. endif
.endif

WORKPLACE=	${.CURDIR:S,${TOPDIR},,:C,^$,/,}
DIRNAME=	${WORKPLACE:C,${WORKPLACE:C,[^/]*$,,},,}

BINDIR?=	${TOPDIR}/bin
LIBDIR?=	${TOPDIR}/lib
SRCDIR?=	${TOPDIR}/src
SRCINCDIR?=	${SRCDIR}/include
INCLUDEDIR?=	${TOPDIR}/include
TESTDIR?=	${TOPDIR}/tests

.include	"ttt.os.mk"

.if defined(LOCALBASE)
INSTALL_TOPDIR?=	${LOCALBASE}
.else
. if ${OS} == "Linux"
INSTALL_TOPDIR?=	/usr
. else
INSTALL_TOPDIR?=	/usr/local
. endif
.endif

INSTALL_BINDIR?=	${INSTALL_TOPDIR}/bin
INSTALL_LIBDIR?=	${INSTALL_TOPDIR}/lib
INSTALL_INCLUDEDIR?=	${INSTALL_TOPDIR}/include
