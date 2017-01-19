/*
 * Copyright (c) 2016,2017 Daichi GOTO
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

struct textset *textsets[] = { cmdtextsets, deftextsets, NULL};

struct textset deftextsets[] = {
	{ "version",		"ja_JP", "バージョン"		},
	{ "usage",		"ja_JP", "使い方" 		},
	{ "name",		"ja_JP", "名前" 		},
	{ "synopsis",		"ja_JP", "書式" 		},
	{ "description", 	"ja_JP", "解説" 		},
	{ "environment",	"ja_JP", "環境変数" 		},
	{ "example", 		"ja_JP", "使用例" 		},
	{ "alias", 		"ja_JP", "別名" 		},
	{ "options", 		"ja_JP", "オプション" 		},
	{ "debug", 		"ja_JP", "デバッグ" 		},
	{ "on", 		"ja_JP", "オン" 		},
	{ "off", 		"ja_JP", "オフ" 		},
	{ "copyright",		"ja_JP", "著作権" 		},
	{ "command_copyright",	"en_",   "2016 ONGS Inc."	},
	TEXTSET_END
};

struct textset cmdtextsets[] __attribute__((__weak__)) = {
	TEXTSET_END
};
