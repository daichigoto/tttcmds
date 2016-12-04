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

#include "command.h"

struct textset cmdtextsets[] = {
	{ "command_version", "en_", VERSION },

	{ "command_name", "en_", CMDNAME },

	{ "command_alias", "en_", ALIAS },

	{ "command_comment", "ja_JP", "指定した列以外の列を出力する" },

	{ "command_comment", "en_", "print columns other than specified" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " [" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N") "|" _ARG("N/M") " "
	  "[" _ARG("N") "|" _ARG("N/M") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },
	
	{ "command_description", "ja_JP", 
	  "指定した列以外の列を出力する。ファイルの指定がないか、-が指定\n"
	  "されている場合には標準入力を使用。" },

	{ "command_description", "en_", 
	  "Print columns other than specified. If " _ARG("file") " is "
	  "a single dash\n(`-') or absent, it reads from the standard "
	  "input." },

	{ "command_options", "ja_JP", 
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("N") "		" _ARG("N") "列を指定\n"
	  _ARG("N/M") "		" _ARG("N") "列から" _ARG("M") "列目を"
	  			"指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("N") "		Specify the " _ARG("N")  "th column.\n"
	  _ARG("N/M") "		Specify the range from the " _ARG("N")
	  			"th to " _ARG("M") "th column.\n"
	  _ARG("file") "\t	Specify the file." },
	
	{ "command_example", "en_", 
	  _P("cat data.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("a b c d e f g h i")
	  _S("A B C D E F G H I")
	  _P("retu_delete 2 4 6 data.ssv")
	  _S("1 3 5 7 8 9")
	  _S("a c e g h i")
	  _S("A C E G H I")
	  _P("retu_delete 1/10 data.ssv")
	  _P("retu_delete 10 data.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("a b c d e f g h i")
	  _S("A B C D E F G H I")
	  _P("") },

	TEXTSET_END
};
