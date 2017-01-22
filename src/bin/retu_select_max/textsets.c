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

	{ "command_comment", "ja_JP", "指定した列の最大値を出力する" },

	{ "command_comment", "en_", "print the maximum value of the "
	  "specified column" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("1") "] " 
	  "[" _OPT("d") " " _ARG("val") "] "
	  "[" _OPT("N") "] "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N") "|"_ARG("N/M") " "
	  "[" _ARG("N") "|" _ARG("N/M") " " _ETC "]\n"
	  "[" _ARG("file") " " _ETC "]" },
	
	{ "command_description", "ja_JP", 
	  "指定した列の最大値を指定した列順で出力する。\n"
	  "\n"
	  _ARG("N") "		" _ARG("N") "列目を指定\n"
	  _ARG("N/M") "		" _ARG("N") "列目から" _ARG("M") 
	  			"列目を指定\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Print the maximum value of the specified column in the "
	  "specified\n column's order.\n"
	  "\n"
	  _ARG("N") "		Specify the " _ARG("N") "th column.\n"
	  _ARG("N/M") "		Specify the range from the " _ARG("N")
	  			"th to " _ARG("M") "th column.\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it reads "
	  "from the\nstandard input." },

	{ "command_options", "ja_JP", 
	  _OPT("1") "		入力の1行目を削除\n"
	  _OPT("d") " " _ARG("val") "\t\t値がなかった場合に出力する値"
	  			"(デフォルトは@)\n"
	  _OPT("N") "		大小比較を文字列ではなく数値で実施\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("1") "		Remove the first line of the input.\n"
	  _OPT("d") " " _ARG("val") "\t\tSpecify the " _ARG("val") " as "
	  			"output value if all values are @"
				"\n\t\t(default is @).\n"
	  _OPT("N") "		Compare numerically by arithmetic value "
	  			"instead of\n\t\tstring.\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file." },

	{ "command_example", "en_", 
	  _P("cat date.ssv")
	  _S("20170101 20150505 20161010")
	  _S("20150101 20150505 20151010")
	  _S("100000000 200000000 3000000")
	  _P("retu_select_max 1/3")
	  _S("20170101 20150505 3000000")
	  _P("retu_select_max -N 1/3")
	  _S("100000000 200000000 20161010")
	  _P("cat data.tag")
	  _S("ID PRICE")
	  _S("000001 12980")
	  _S("000002 9800")
	  _P("retu_select_max 1/2 data.tag")
	  _S("ID PRICE")
	  _P("retu_select_max -1 1/2 data.tag")
	  _S("000002 9800")
	  _P("retu_select_max -1 -N 1/2 data.tag")
	  _S("000002 12980")
	  _P("echo | retu_select 5")
          _S("@")
	  _P("echo | retu_select -d 000001 5")
          _S("000001")
	  _P("") },

	TEXTSET_END
};
