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

CMD?=		$(DIRNAME).exe

SRCS?=		$(wildcard *.c)
OBJS?=		$(SRCS:.c=.o)

_aliases=	$(shell	grep '#define ALIAS' command.h		| \
			sed 's/#define ALIAS //'		| \
			sed 's/"//g'				)
ALIASES=	$(_aliases:=.exe)

ifndef all
all: build
endif

ifndef prebuild
prebuild:
endif

ifndef preclean
preclean:
endif

ifneq ($(CMD),)
build: install-required-packages prebuild $(CMD)

$(CMD): $(OBJS)
	$(CC) $(CFLAGS) -o $(CMD) $(OBJS) $(LINKFLAGS)
else
build: install-required-packages prebuild $(OBJS)

$(CMD): 
endif

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

install: build $(BINDIR)/$(CMD)

$(BINDIR)/$(CMD): $(CMD)
	for i in $(CMD) $(ALIASES); \
	do \
		install -m $(BINPERM) $(CMD) $(BINDIR)/$${i}; \
	done

uninstall: 
	for i in $(CMD) $(ALIASES); \
	do \
		rm -f $(BINDIR)/$${i}; \
	done

clean: preclean
	rm -f $(CMD) $(OBJS)

test: install
	cd $(TESTDIR)/bin/$(DIRNAME); $(MAKE) $@

install-required-packages:
#--------------------------------------------------------------------
# libttt
#--------------------------------------------------------------------
ifneq ($(wildcard $(SRCLIBDIR)/libttt/getcmdargs.o),$(SRCLIBDIR)/libttt/getcmdargs.o)
	cd $(SRCLIBDIR)/libttt/; $(MAKE) build
endif

#--------------------------------------------------------------------
# Berkeley DB 4 (1.85 compatible API)
#--------------------------------------------------------------------
ifdef NEED_BDB185
 ifneq ($(wildcard /usr/include/db_185.h),/usr/include/db_185.h)
	pacman -S --noconfirm libdb-devel
 endif
endif
