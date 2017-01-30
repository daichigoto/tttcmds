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

#include "command.h"

struct textset cmdtextsets[] = {
	{ "command_version", "en_", VERSION },

	{ "command_name", "en_", CMDNAME },

	{ "command_alias", "en_", ALIAS },

	{ "command_copyright", "en_", "2016,2017 ONGS Inc." },

	{ "command_comment", "ja_JP", "SSVデータを指定された列で比較" },

	{ "command_comment", "en_", 
	  "compare the specified two SSV data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N") "|"_ARG("N/M") " "
	  "[" _ARG("N") "|" _ARG("N/M") " " _ETC "] "
	  _ARG("file_src") " " _ARG("file_new") },
	
	{ "command_description", "ja_JP", 
	  "2つのSSVデータを指定された列で比較し差分を出力する。\n"
	  "\n"
	  _ARG("N") "\t\t" 	_ARG("N") "列目を指定\n"
	  _ARG("N/M") "\t\t"	_ARG("N") "と同じ処理を" _ARG("M")
	 			"列まで適用\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Compare the two specified SSV data row by row and column and\n"
	  "column, and print the differential data.\n"
	  "\n"
	  _ARG("N") "		Specify the " _ARG("N") "th column.\n"
	  _ARG("N/M") "		Process the " _ARG("N") "th to " _ARG("M")
	  			"th columns in the same way "
				"\n\t\tas " _ARG("N") ".\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it reads "
	  "from the\nstandard input." },

	{ "command_options", "ja_JP", 
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file_src") "	比較元データを指定\n"
	  _ARG("file_new") "	比較対象データを指定" },
	
	{ "command_options", "en_", 
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file_src") "	Specify the source data.\n" 
	  _ARG("file_new") "	Specify the target data." },

	{ "command_example", "en_", 
	  _P("cat data.ssv")
	  _S("1 2 3 4 5 @ 7 8 9")
	  _S("a b @ d e f g h i")
	  _S("A B C D E F @ H I")
	  _P("cat new.ssv")
	  _S("1 2 3 4 5 . @ @ @")
	  _S("a b @ d e f G @ @")
	  _S("A B C D E F @ @ @")
	  _P("retu_diff 1/5 data.ssv new.ssv")
	  _P("retu_deff 1/6 data.ssv new.ssv")
	  _S("1 2 3 4 5 . @ @ @")
	  _P("retu_deff 1/7 data.ssv new.ssv")
	  _S("1 2 3 4 5 . @ @ @")
	  _S("a b @ d e f G @ @")
	  _P("retu_deff 1/8 data.ssv new.ssv")
	  _S("1 2 3 4 5 . @ @ @")
	  _S("a b @ d e f G @ @")
	  _S("A B C D E F @ @ @")
	  _P("") },

	TEXTSET_END
};
