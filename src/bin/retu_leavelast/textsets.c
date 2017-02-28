/*
 * Copyright (c) 2017 Daichi GOTO
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

	{ "command_copyright", "en_", "2016,2017 ONGS Inc." },

	{ "command_comment", "ja_JP", 
	  "指定された列の連続するデータの最後を出力する" },

	{ "command_comment", "en_", 
	  "print first to one before last as empty data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("hvD") "] [" _OPT("-") "] " 
	  _ARG("N") "|" _ARG("N/M") " "
	  "[" _ARG("N") "|" _ARG("N/M") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "指定された列で同じデータが連続している場合、最後のデータのみ\n"
	  "出力してそれ以外のデータは空データとして出力する。ファイルの\n"
	  "指定がないか、-が指定されている場合には標準入力を使用。" },

	{ "command_description", "en_", 
	  "Print from the first to one before last data as empty from\n"
	  "the sequential range that have the same data for each\n"
	  "specified column. If " _ARG("file") " is a single dash (`-') "
	  "or absent,\nit reads from the standard input." },

	{ "command_options", "ja_JP", 
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("N") "		" _ARG("N") "列目を指定\n"
	  _ARG("N/M") "		" _ARG("N") "列目から" _ARG("M") "列目を"
	  			"指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	 
	{ "command_options", "en_", 
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("N") "		Specify the " _ARG("N") "th column.\n"
	  _ARG("N/M") "		Specify the range from the " _ARG("N") 
	  			"th to " _ARG("M") "th column.\n"
	  _ARG("file") "\t	Specify the file." },

	{ "command_example", "en_", 
	  _P("cat data.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("1 @ 3 4 5 6 7 8 9")
	  _S("1 2 @ 4 5 6 7 8 9")
	  _S("1 @ 3 @ 5 6 7 8 9")
	  _S("1 @ 3 4 @ 6 7 8 9")
	  _S("1 @ 3 4 5 @ 7 8 9")
	  _S("1 @ 3 4 5 6 @ 8 9")
	  _P("retu_leavelast 1 data.ssv")
	  _S("@ 2 3 4 5 6 7 8 9")
	  _S("@ @ 3 4 5 6 7 8 9")
	  _S("@ 2 @ 4 5 6 7 8 9")
	  _S("@ 2 3 @ 5 6 7 8 9")
	  _S("@ 2 3 4 @ 6 7 8 9")
	  _S("@ 2 3 4 5 @ 7 8 9")
	  _S("1 2 3 4 5 6 @ 8 9")
	  _P("retu_leavelast 3 data.ssv")
	  _S("1 2 @ 4 5 6 7 8 9")
	  _S("1 @ 3 4 5 6 7 8 9")
	  _S("1 2 @ 4 5 6 7 8 9")
	  _S("1 @ @ @ 5 6 7 8 9")
	  _S("1 @ @ 4 @ 6 7 8 9")
	  _S("1 @ @ 4 5 @ 7 8 9")
	  _S("1 @ 3 4 5 6 @ 8 9")
	  _P("retu_leavelast 1/9 data.ssv")
	  _S("@ 2 @ @ @ @ @ @ @")
	  _S("@ @ 3 @ @ @ @ @ @")
	  _S("@ 2 @ 4 @ @ @ @ @")
	  _S("@ @ @ @ 5 @ @ @ @")
	  _S("@ @ @ @ @ 6 @ @ @")
	  _S("@ @ @ @ @ @ 7 @ @")
	  _S("1 @ 3 4 5 6 @ 8 9")
	  _P("") },

	TEXTSET_END
};
