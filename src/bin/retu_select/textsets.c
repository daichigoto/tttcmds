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

	{ "command_comment", "ja_JP", "指定した順で指定した列を出力する" },

	{ "command_comment", "en_", "print the specified columns in the "
	  "specified order" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("1") "] " 
	  "[" _OPT("e") "] " 
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N") "|"_ARG("N/M") "|"
	  _ARG("N.k.s") "|"_ARG("N/M.k.s") " "
	  "[" _ARG("N") "|" _ARG("N/M") "|\n" 
	      _ARG("N.k.s") "|" _ARG("N/M.k.s") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },
	
	{ "command_description", "ja_JP", 
	  "指定した順で指定した列を出力する。\n"
	  "\n"
	  ES_BOLD("単純出力") "\n"
	  _ARG("N") "\t\t" 	_ARG("N") "列目を出力\n"
	  _ARG("N/M") "\t\t"	_ARG("N") "と同じ処理を" _ARG("M")
	 			"列まで適用\n"
	  "\n"
	  ES_BOLD("置換出力") "\n"
	  _ARG("N.k.s") "\t\t" 	_ARG("N") "列目の値が" _ARG("k") 
	  			"だった場合に" _ARG("s") "を出力、"
				"そうでない場合には\n\t\t" _ARG("N") 
				"列の値を出力\n"
	  _ARG("N/M.k.s") "\t\t" _ARG("N.k.s") "と同じ処理を" _ARG("M")
	 			"列まで適用\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Print the specified columns in the specified order.\n"
	  "\n"
	  ES_BOLD("SIMPLE PRINT") "\n"
	  _ARG("N") "		Print the value of the " _ARG("N") "th "
	  			"column.\n"
	  _ARG("N/M") "		Process the " _ARG("N") "th to " _ARG("M")
	  			"th columns in the same way "
				"\n\t\tas " _ARG("N") ".\n"
	  "\n"
	  ES_BOLD("SWAP PRINT") "\n"
	  _ARG("N.k.s") "\t	Print the value of the " _ARG("N") "th "
	  			"column if it and " _ARG("k") "\n"
				"\t\tdon't match, or print " _ARG("s") ".\n"
	  _ARG("N/M.k.s") "\t	Process the " _ARG("N") "th to " _ARG("M")
	  			"th columns in the same way "
				"\n\t\tas " _ARG("N.k.s") ".\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it reads "
	  "from the\nstandard input." },

	{ "command_options", "ja_JP", 
	  _OPT("1") "		入力の1行目を削除\n"
	  _OPT("e") "		出力が何もなかった場合、1行だけ空行を"
	  			"処理\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("1") "		Remove the first line of the input.\n"
	  _OPT("e") "		Process the empty line if no output.\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file." },

	{ "command_example", "en_", 
	  _P("cat data1.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _P("retu_select 9 7 3 4 2 1 8 3 1 1 1 data1.ssv")
	  _S("9 7 3 4 2 1 8 3 1 1 1")
	  _P("retu_select 2/5 2/5 2/5 data1.ssv")
	  _S("2 3 4 5 2 3 4 5 2 3 4 5")
	  _P("retu_select 9/1 data1.ssv")
	  _S("9 8 7 6 5 4 3 2 1")
	  _P("retu_select 0 0 1 10 10 data1.ssv")
	  _S("@ @ 1 @ @")
	  _P("cat data2.ssv")
	  _S("A")
	  _P("retu_select 1/9 data1.ssv data2.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("A @ @ @ @ @ @ @ @")
	  _P("retu_select 1:A:1 2/9 data1.ssv data2.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("1 @ @ @ @ @ @ @ @")
	  _P("retu_select 1/9::0 data1.ssv data2.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("A 0 0 0 0 0 0 0 0")
	  _P("retu_select 1/15 data1.ssv data2.ssv")
	  _S("1 2 3 4 5 6 7 8 9 @ @ @ @ @ @")
	  _S("A @ @ @ @ @ @ @ @ @ @ @ @ @ @")
	  _P("cat price.tag")
	  _S("ID PRICE")
	  _S("000001 12800")
	  _S("000002 9800")
	  _P("retu_select -1 1/3 price.tag")
	  _S("000001 12800 @")
	  _S("000002 9800 @")
	  _P("printf '' | retu_select 1/10")
	  _P("printf '' | retu_select -e 1/10..NON")
	  _S("NON NON NON NON NON NON NON NON NON NON")
	  _P("") },

	TEXTSET_END
};
