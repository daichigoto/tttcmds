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

	{ "command_comment", "ja_JP",
	  "日時形式を変換して出力" },

	{ "command_comment", "en_",
	  "convert the format of date to another" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N.f1.f2") "|" _ARG("N/M.f1.f2") " "
	  "[" _ARG("N.f1.f2") "|\n" _ARG("N/M.f1.f2") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "指定した列の日時形式を変換して出力。\n"
	  "\n"
	  _ARG("N.f1.f2") "\t\t" _ARG("N") "列の日付データを" _ARG("f1")
	  	"フォーマットで読み込み、" _ARG("f2") "\n\t\t"
		"フォーマットに変換して出力する。フォーマットは\n\t\t"
		"strptime(3)に準拠\n"
	  _ARG("N/M.f1.f2") "\t" _ARG("N.f1.f2") "と同じ処理を" 
	  	_ARG("M") "列まで適用\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Convert the format of specified column's date to the another.\n"
	  "\n"
	  _ARG("N.f1.f2") "\t\tConvert the date value of " _ARG("N") 
	  	"th column to another.\n\t\t" _ARG("f1") " is the src "
		"format and " _ARG("f2") " is the dst format\n\t\t"	
		"based on strptime(3).\n"
	  _ARG("N/M.f1.f2") "\tProcess " _ARG("N") "th to " _ARG("M")
		"th columns in the same way as\n\t\t" _ARG("N.f1.f2") ".\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it reads "
	  "from the\nstandard input." },

	{ "command_options", "ja_JP", 
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file." },
	
	{ "command_example", "en_", 
	  _P("cat data1.ssv")
	  _S("20161109121423 20161110085400")
	  _P("cat data1.ssv |")
	  _P2("retu_dateformat \\")
	  _P2("	1.%Y%m%d%H%M%S.%Y/%m/%d-%H:%M \\")
	  _P2("	2.%Y%m%d%H%M%S.%Y/%m/%d-%H:%M")
	  _S("2016/11/09-12:14 2016/11/10-08:54")
	  _P("cat data2.ssv")
	  _S("2016/11/09-12:14 2016/11/10-08:54")
	  _P("cat data2.ssv |")
	  _P2("retu_dateformat \\")
	  _P2("	1.%Y/%m/%d-%H:%M.%Y%m%d%H%M%S \\")
	  _P2("	2.%Y/%m/%d-%H:%M.%Y%m%d%H%M%S")
	  _S("20161109121401 20161110085401")
	  _P("cat data1.ssv |")
	  _P2("retu_dateformat 1/2.%Y%m%d%H%M%S.%Y/%m/%d-%H:%M")
	  _S("2016/11/09-12:14 2016/11/10-08:54")
	  _P("cat data1.ssv |")
	  _P2("retu_dateformat 1.%Y%m%d%H%M%S.%s 2.%Y%m%d%H%M%S.%s")
	  _S("1478661263 1478735640")
	  _P("cat data1.ssv |")
	  _P2("retu_dateformat 1.%Y%m%d%H%M%S.%s 2.%Y%m%d%H%M%S.%s |")
	  _P2("retu_dateformat 1.%s.\"%m/%d %H:%M\" 2.%s.\"%m/%d %H:%M\"")
	  _S("11/09_12.14 11/10_08.54")
	  _P("cat data1.ssv |")
	  _P2("retu_dateformat 1/2.%Y%m%d%H%M%S.%A(%a)")
	  _S("Tuesday(Tue) Wednesday(Wed)")
	  _P("cat data1.ssv |")
	  _P2("env LANG=ja_JP.UTF-8 retu_dateformat 1/2.%Y%m%d%H%M%S.%A(%a)")
	  _S("火曜日(火) 水曜日(水)")
	  _P("") },

	TEXTSET_END
};
