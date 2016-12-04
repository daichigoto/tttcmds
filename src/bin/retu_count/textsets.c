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

	{ "command_comment", "ja_JP", "列数をカウントする" },

	{ "command_comment", "en_", "count the number of columns" },

	{ "command_synopsis", "en_",
	  _CMD(CMDNAME) " "
	  "[" _OPT("nf") "] [" _OPT("hvD") "] [" _OPT("-") "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "列数をカウントする。ファイルの指定がないか、-が指定されている\n"
	  "場合には標準入力を使用。" },

	{ "command_description", "en_", 
	  "Count the number of columns. If " _ARG("file") " is a single "
	  "dash (`-') or\nabsent, it reads from the standard input." },

	{ "command_options", "ja_JP", 
	  _OPT("f") "		ファイル名とファイルごとの行数を出力\n"
	  _OPT("n") "		行数を出力\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	 
	{ "command_options", "en_", 
	  _OPT("f") "		Print the number of lines for each file.\n"
	  _OPT("n") "		Print the number of lines.\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file." },
	 
	{ "command_example", "en_", 
	  _P("cat data1.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("a b c d")
	  _S(" a b c d")
	  _P("retu_count data1.ssv")
	  _S("9")
	  _S("4")
	  _S("5")
	  _P("retu_count -n data1.ssv")
	  _S("1: 9")
	  _S("2: 4")
	  _S("3: 5")
	  _P("cat data2.ssv")
	  _S("A")
	  _S("B")
	  _P("retu_count data1.ssv data2.ssv")
	  _S("9")
	  _S("4")
	  _S("5")
	  _S("1")
	  _P("retu_count -n -f data1.ssv data2.ssv")
	  _S("data1.ssv:1:1: 9")
	  _S("data1.ssv:2:2: 4")
	  _S("data1.ssv:3:3: 5")
	  _S("data2.ssv:1:4: 1")
	  _P("") },

	TEXTSET_END
};
