/*
 * Copyright (c) 2017,2019,2021 Daichi GOTO
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

        { "command_copyright", "en_", "2016,2017,2019 ONGS Inc." },

	{ "command_comment", "ja_JP", "列に値を割り当てる" },

	{ "command_comment", "en_",
	  "assign values to specified columns" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " " 
	  "[" _OPT("@") " " _ARG("val") "] "
	  "[" _OPT("f") " " _ARG("file") "] "
	  "[" _OPT("m") " " _ARG("simple|condition|join") "]\n"
	  "[" _OPT("s") "] "
	  "[" _OPT("hvD") "] [" _OPT("-") "]\n" 
	  _ARG("N.a") "|" _ARG("N.p.s") "|" 
	  _ARG("N!p!s") "|" _ARG("N.f.K.A")  "|" 
	  _ARG("N/M.a") "|" _ARG("N/M.p.s") "|" 
	  _ARG("N/M!p!s") "|" _ARG("N/M.f.K.A") "\n"
	  "[" _ARG("N.a") "|" _ARG("N.p.s") "|"
	      _ARG("N!p!s") "|" _ARG("N.f.K.A") "|"
	      _ARG("N/M.a") "|" _ARG("N/M.p.s") "|" 
	      _ARG("N/M!p!s") "|" _ARG("N/M.f.K.A") " " _ETC "]\n"
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "いくつかの方法で列に値を割り当てることが可能。\n"
	  "\n"
	  ES_BOLD("単純代入 (-f指定なし)") "\n"
	  _ARG("N.a") "\t\t" _ARG("a") "を" _ARG("N") "列に代入\n"
	  _ARG("N/M.a") "\t\t" _ARG("N.a") "と同じ処理を" _ARG("M") 
	  	"列まで適用\n"
	  "\n"
	  ES_BOLD("単純代入 (-f指定あり)") "\n"
	  _ARG("N.n") "\t\t" _ARG("file") "の1行目" _ARG("n") "列目の"
	  	"値を" _ARG("N") "列に代入\n"
	  _ARG("N/M.n") "\t\t" _ARG("N.a") "と同じ処理を" _ARG("M") 
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
		"列に代入。一致しない場合には空デー\n\t\tタを出力\n"
	  _ARG("N/M.f.K.A") "\t" _ARG("N.f.K.A") "と同じ処理を"
	  	_ARG("M") "列まで適用\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Assign values to specified columns in several ways as below.\n"
	  ""
	  "\n"
	  ES_BOLD("SIMPLE ASSIGNMENT (without -f)") "\n"
	  _ARG("N.a") "\t\tAssign " _ARG("a") " to " _ARG("N") "th "
	  	"column.\n"
	  _ARG("N/M.a") "\t\tProcess " _ARG("N") "th to " _ARG("M") "th "
	  	"columns in the same way as\n\t\t" _ARG("N.a") ".\n"
	  "\n"
	  ES_BOLD("SIMPLE ASSIGNMENT (with -f)") "\n"
	  _ARG("N.a") "\t\tAssign the value of 1st row " _ARG("n") 
	  	"th column of the\n\t\t" _ARG("file") " to " _ARG("N") 
		"th column.\n"
	  _ARG("N/M.a") "\t\tProcess " _ARG("N") "th to " _ARG("M") "th "
	  	"columns in the same way as\n\t\t" _ARG("N.a") ".\n"
	  "\n"
	  ES_BOLD("CONDITIONAL ASSIGNMENT") "\n"
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
		"\n\t\tassing the empty value.\n"
	  _ARG("N/M.f.K.A") "\t" "Process " _ARG("N") "th to " _ARG("M") 
	  	"th columns in the same way as\n\t\t" _ARG("N.f.K.A") ".\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it "
	  "reads from the\nstandard input." },

	{ "command_options", "ja_JP", 
	  _OPT("@") " " _ARG("val") "\t\t結合代入で値がなかった場合に"
	  			"出力する値\n\t\t(デフォルトは@)\n"
	  _OPT("f") " " _ARG("file") "\t\t単純代入で使うファイルを指定\n"
	  _OPT("m") " " _ARG("mode") "\t\t代入モードを指定\n"
	  			"\t\tsimple\t\t- 単純代入\n"
	  			"\t\tcondition\t- 条件代入\n"
	  			"\t\tjoin\t\t- 結合代入\n"
	  _OPT("s") "		" _ARG("a") "をSSV文字列として扱う\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("@") " " _ARG("val") "\t\tSpecify the " _ARG("val") " as "
	  			"output value if the assignment "
				"\n\t\tvalues are @ (default is @).\n"
	  _OPT("f") " " _ARG("file") "\t\tSpecify the " _ARG("file") 
	  			" for simple assignment.\n"
	  _OPT("m") " " _ARG("mode") "\t\tSpecify the assign mode.\n"
	  			"\t\tsimple\t\t- SIMPLE ASSIGNMENT\n"
	  			"\t\tcondition\t- CONDITIONAL ASSIGNMENT\n"
	  			"\t\tjoin\t\t- JOIN ASSIGNMENT\n"
	  _OPT("s") "		Handle " _ARG("a") "as a SSV string.\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file." },

	{ "command_example", "en_", 
	  _P1("cat data.ssv") 
	  _ST("aa @ cc dd ee ff gg hh ii jj kk")
	  _P1("retu_assign 1.AA 3.CC 4/7.DD data.ssv") 
	  _ST("AA @ CC DD DD DD DD hh ii jj kk")
	  _P1("retu_assign 1/11.'' data.ssv") 
	  _ST("@ @ @ @ @ @ @ @ @ @ @")
	  _P1("cat data.ssv") 
	  _ST("aa @ cc dd ee ff gg hh ii jj kk")
	  _P1("retu_assign 1.aa.AA 2.aa.AA 3.aa.AA data.ssv") 
	  _ST("AA @ cc dd ee ff gg hh ii jj kk")
	  _P1("retu_assign 1!aa!AA 2!aa!AA 3!aa!AA data.ssv") 
	  _ST("aa AA AA dd ee ff gg hh ii jj kk")
	  _P1("1.aa.AA 1!aa!cc data.ssv")
	  _ST("AA @ cc dd ee ff gg hh ii jj kk")
	  _P1("retu_assign 1/11..0 data.ssv") 
	  _ST("aa 0 cc dd ee ff gg hh ii jj kk")
	  _P1("retu_assign 1/11!!0 data.ssv") 
	  _ST("0 @ 0 0 0 0 0 0 0 0 0")
	  _P1("cat name.ssv") 
	  _ST("000001 APPLE")
	  _ST("000002 MIKAN")
	  _ST("000003 BANANA")
	  _ST("000004 BLUEBERRY")
	  _ST("000005 MELON")
	  _P1("cat farm.ssv")
	  _ST("000001 CHINA U.S.")
	  _ST("000002 JAPAN U.K.")
	  _ST("000003 INDIA PHILIPPINES") 
	  _ST("000004 U.S. CANADA")
	  _ST("000005 CHINA TURKEY")
	  _P1("cat sales.ssv") 
	  _ST("000003 100")
	  _ST("000001 220")
	  _ST("000002 120")
	  _ST("000004 0")
	  _ST("000005 230")
	  _ST("000100 0")
	  _P1("retu_select 1 1 1 2 sales.ssv") 
	  _ST("000003 000003 000003 100")
	  _ST("000001 000001 000001 220")
	  _ST("000002 000002 000002 120")
	  _ST("000004 000004 000004 0")
	  _ST("000005 000005 000005 230")
	  _ST("000100 000100 000100 0")
	  _P1("retu_select 1 1 1 2 sales.ssv |") 
	  _P2("retu_assign -@ NONE 2:name.ssv:1:2 3:farm.ssv:1:2,3") 
	  _ST("000003 BANANA INDIA PHILIPPINES 100")
	  _ST("000001 APPLE CHINA U.S. 220")
	  _ST("000002 MIKAN JAPAN U.K. 120")
	  _ST("000004 BLUEBERRY U.S. CANADA 0")
	  _ST("000005 MELON CHINA TURKEY 230")
	  _ST("000100 NONE NONE NONE 0")
	  _P1("retu_select 1 1 1 2 sales.ssv |") 
	  _P2("retu_assign -m simple -@ NONE 2:name.ssv:1:2 3:farm.ssv:1:2,3") 
	  _ST("000003 name.ssv:1:2 farm.ssv:1:2,3 100")
	  _ST("000001 name.ssv:1:2 farm.ssv:1:2,3 220")
	  _ST("000002 name.ssv:1:2 farm.ssv:1:2,3 120")
	  _ST("000004 name.ssv:1:2 farm.ssv:1:2,3 0")
	  _ST("000005 name.ssv:1:2 farm.ssv:1:2,3 230")
	  _ST("000100 name.ssv:1:2 farm.ssv:1:2,3 0")
	  _P1("retu_select 1 1 1 2 sales.ssv |") 
	  _P2("retu_assign -@ NONE 2:name.ssv:1:2 3:farm.ssv:1:2,3 |") 
	  _P2("retu_assign -f data.ssv 1.2 3.1 4.7") 
	  _ST("@ BANANA aa gg 100")
	  _ST("@ APPLE aa gg 220")
	  _ST("@ MIKAN aa gg 120")
	  _ST("@ BLUEBERRY aa gg 0")
	  _ST("@ MELON aa gg 230")
	  _ST("@ NONE aa gg 0")
	  _P1("retu_assign 1/11.@ data.ssv") 
	  _ST("\\@ \\@ \\@ \\@ \\@ \\@ \\@ \\@ \\@ \\@ \\@")
	  _P1("retu_assign -s 1/11.@ data.ssv") 
	  _ST("@ @ @ @ @ @ @ @ @ @ @")
	  _P1("echo @ | retu_assign -m condition 1::=::=") 
	  _ST("=::=")
	  _P1("") },

	TEXTSET_END
};
