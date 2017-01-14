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

	{ "command_comment", "ja_JP", "列に値を割り当てる" },

	{ "command_comment", "en_",
	  "assign values to specified columns" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " " 
	  "[" _OPT("hvD") "] [" _OPT("-") "] " 
	  _ARG("N.a") "|" _ARG("N.p.s") "|" _ARG("N!p!s") "|"
	  _ARG("N.f.K.A")  "|" _ARG("N/M.a") "|" _ARG("N/M.p.s") "|\n"
	  _ARG("N/M!p!s") "|" _ARG("N/M.f.K.A") " "
	  "[" _ARG("N.a") "|" _ARG("N.p.s") "|" _ARG("N!p!s") "|" 
	      _ARG("N.f.K.A") "|" _ARG("N/M.a") "|" _ARG("N/M.p.s") "|" 
	      _ARG("N/M!p!s") "|\n" _ARG("N/M.f.K.A") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "いくつかの方法で列に値を割り当てることが可能。\n"
	  "\n"
	  ES_BOLD("単純代入") "\n"
	  _ARG("N.a") "\t\t" _ARG("a") "を" _ARG("N") "列に代入\n"
	  _ARG("N/M.a") "\t\t" _ARG("N.a") "と同じ処理を" _ARG("M") 
	  	"列まで適用\n"
	  "\n"
	  ES_BOLD("条件代入") "\n"
	  _ARG("N.p.s") "\t\t" _ARG("N") "列の値が" _ARG("p") 
	  	"に一致した場合、" _ARG("s") "を" _ARG("N") "列に代入"
		"(デリミタは\n\t\t" _ARG("!") "以外)\n"
	  _ARG("N!p!s") "\t\t" _ARG("N") "列の値が" _ARG("p") 
	  	"に一致しなかった場合、" _ARG("s") "を" _ARG("N") 
		"列に代入(デリ\n\t\tミタは" _ARG("!") ")\n"
	  _ARG("N/M.p.s") "\t\t" _ARG("N.p.s") "と同じ処理を"
	  	_ARG("M") "列まで適用\n"
	  _ARG("N/M!p!s") "\t\t" _ARG("N!p!s") "と同じ処理を"
	  	_ARG("M") "列まで適用\n"
	  "\n"
	  ES_BOLD("結合代入") "\n"
	  _ARG("N.f.K.A") "\t\t" _ARG("N") "列の値と" _ARG("f") "ファイル"
	  	"の" _ARG("K") "列の値が一致する場合、" _ARG("f") 
		"ファ\n\t\tイルの" _ARG("A") "列の値を" _ARG("N") 
		"列に代入。一致しない場合には空デー\n\t\tタを出力"
		"(左外部結合)\n"
	  _ARG("N/M.f.K.A") "\t" _ARG("N.f.K.A") "と同じ処理を"
	  	_ARG("M") "列まで適用\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Assign values to specified columns in several ways as below.\n"
	  ""
	  "\n"
	  ES_BOLD("SIMPLE ASSIGNMENT") "\n"
	  _ARG("N.a") "\t\tAssign " _ARG("a") " to " _ARG("N") "th "
	  	"column.\n"
	  _ARG("N/M.a") "\t\tProcess " _ARG("N") "th to " _ARG("M") "th "
	  	"columns in the same way as\n\t\t" _ARG("N.a") ".\n"
	  "\n"
	  ES_BOLD("CONDITION ASSIGNMENT") "\n"
	  _ARG("N.p.s") "\t\tAssign " _ARG("s") " to the " _ARG("N") "th " 
	  	"column if " _ARG("p") " and the value\n\t\tof " 
		_ARG("N") "th column match. The delimiter is not '!'.\n"
	  _ARG("N!p!s") "\t\tAssign " _ARG("s") " to the " _ARG("N") "th "
	  	"column if " _ARG("p") " and the value\n\t\tof "
		_ARG("N") "th column don't match. The delimiter is '!'.\n"
	  _ARG("N/M.p.s") "\t\tProcess " _ARG("N") "th to " _ARG("M") 
	  	"th columns in the same way as\n\t\t" _ARG("N.p.s") ".\n"
	  _ARG("N/M!p!s") "\t\tProcess " _ARG("N") "th to " _ARG("M") 
	  	"th columns in the same way as\n\t\t" _ARG("N!p!s") ".\n"
	  "\n"
	  ES_BOLD("JOIN ASSIGNMENT") "\n"
	  _ARG("N.f.K.A") "\t\tAssign the value of " _ARG("A") "th "
	  	"column of the file " _ARG("f") "\n\t\tto the " _ARG("N") 
		"th column if the value of " _ARG("N") "th column\n\t\t"
		"and the value of " _ARG("K")  "th column match. If not, "
		"\n\t\tassing the empty value. "
		"(a.k.a LEFT OUTER JOIN).\n"
	  _ARG("N/M.f.K.A") "\t" "Process " _ARG("N") "th to " _ARG("M") 
	  	"th columns in the same way as\n\t\t" _ARG("N.f.K.A") ".\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it "
	  "reads from the\nstandard input." },

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
	  _P("cat data.ssv") 
	  _S("aa @ cc dd ee ff gg hh ii jj kk")
	  _P("retu_assign 1.AA 3.CC 4/7.DD data.ssv") 
	  _S("AA @ CC DD DD DD DD hh ii jj kk")
	  _P("retu_assign 1/11.'' data.ssv") 
	  _S("@ @ @ @ @ @ @ @ @ @ @")
	  _P("cat data.ssv") 
	  _S("aa @ cc dd ee ff gg hh ii jj kk")
	  _P("retu_assign 1.aa.AA 2.aa.AA 3.aa.AA data.ssv") 
	  _S("AA @ cc dd ee ff gg hh ii jj kk")
	  _P("retu_assign 1!aa!AA 2!aa!AA 3!aa!AA data.ssv") 
	  _S("aa AA AA dd ee ff gg hh ii jj kk")
	  _P("1.aa.AA 1!aa!cc data.ssv")
	  _S("AA @ cc dd ee ff gg hh ii jj kk")
	  _P("retu_assign 1/11..0 data.ssv") 
	  _S("aa 0 cc dd ee ff gg hh ii jj kk")
	  _P("retu_assign 1/11!!0 data.ssv") 
	  _S("0 @ 0 0 0 0 0 0 0 0 0")
	  _P("cat name.ssv") 
	  _S("000001 APPLE")
	  _S("000002 MIKAN")
	  _S("000003 BANANA")
	  _S("000004 BLUEBERRY")
	  _S("000005 MELON")
	  _P("cat farm.ssv")
	  _S("000001 CHINA U.S.")
	  _S("000002 JAPAN U.K.")
	  _S("000003 INDIA PHILIPPINES") 
	  _S("000004 U.S. CANADA")
	  _S("000005 CHINA TURKEY")
	  _P("cat sales.ssv") 
	  _S("000003 100")
	  _S("000001 220")
	  _S("000002 120")
	  _S("000004 0")
	  _S("000005 230")
	  _S("000100 0")
	  _P("retu_select 1 1 1 2 sales.ssv") 
	  _S("000003 000003 000003 100")
	  _S("000001 000001 000001 220")
	  _S("000002 000002 000002 120")
	  _S("000004 000004 000004 0")
	  _S("000005 000005 000005 230")
	  _S("000100 000100 000100 0")
	  _P("retu_select 1 1 1 2 sales.ssv |") 
	  _P2("retu_assign 2:name.ssv:1:2 3:farm.ssv:1:2,3") 
	  _S("000003 BANANA INDIA PHILIPPINES 100")
	  _S("000001 APPLE CHINA U.S. 220")
	  _S("000002 MIKAN JAPAN U.K. 120")
	  _S("000004 BLUEBERRY U.S. CANADA 0")
	  _S("000005 MELON CHINA TURKEY 230")
	  _S("000100 @ @ @ 0")
	  _P("") },

	TEXTSET_END
};
