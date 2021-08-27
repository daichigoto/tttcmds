/*
 * Copyright (c) 2017,2021 Daichi GOTO
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

	{ "command_copyright", "en_", "2017 ONGS Inc." },

	{ "command_comment", "ja_JP", "2つのSSVデータを左外部結合する" },

	{ "command_comment", "en_", "Leftouterjoin two SSV data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("r") "] "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("L=R") "|"_ARG("L/L2=R") " "
	  "[" _ARG("L=R") "|" _ARG("L/L2=R") " " _ETC "]\n"
	  _ARG("file_left") " " _ARG("file_right") },
	
	{ "command_description", "ja_JP", 
	  "2つのSSVデータを左外部結合する。\n"
	  "\n"
	  _ARG("L=R") "\t\t" 	_ARG("file_left") "の" _ARG("L") "と"
	  			_ARG("file_right") "の" _ARG("R") "を"
				"一致条件として左外部結合\n"
	  _ARG("L/L2=R") "\t\t"	_ARG("L=R") "と同じ処理を" _ARG("L2")
	 			"列まで適用\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Leftouterjoin two SSV data. \n"
	  "\n"
	  _ARG("L=R") "\t\t" 	"Leftouterjoin "
	  			_ARG("file_left") " and "
				_ARG("file_right") " where the value\n\t\t"
				"of " _ARG("L") "th column "
				"of " _ARG("file_left") " and the value "
				"of " _ARG("R") "th\n\t\tcolumn "
				"of " _ARG("file_right") " match.\n" 
	  _ARG("L/L2=R") "\t\t"	"Process the " _ARG("L") "th to " _ARG("L2")
	  			"th columns in the same way "
				"\n\t\tas " _ARG("L=R") ".\n"
	  "\n"
	  "If " _ARG("file_left") " or " _ARG("file_right") " is "
	  "a single dash (`-') or absent, it reads\nfrom the standard "
	  "input." },

	{ "command_options", "ja_JP", 
	  _OPT("r") "		結合データ(右)からR列を削除する\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file_left") "	左SSVデータファイルを指定\n"
	  _ARG("file_right") "	右SSVデータファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("r") "		Remove " _ARG("R")  "th column from "
	  			"the joined data (from right).\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file_left") "	Specify the left SSV data.\n" 
	  _ARG("file_right") "	Specify the right SSV data." },

	{ "command_example", "en_", 
	  _P1("cat left.ssv")
	  _ST("001 AAA")
	  _ST("002 AAA")
	  _ST("003 BBB")
	  _ST("001 AAA")
	  _P1("cat right.ssv")
	  _ST("AAA 002 a")
	  _ST("CCC 003 c")
	  _ST("CCC 003 d")
	  _ST("AAA 004 a")
	  _P1("join_leftouterjoin 1=2 left.ssv right.ssv")
	  _ST("001 AAA @ @ @")
	  _ST("002 AAA AAA 002 a")
	  _ST("003 BBB CCC 003 c")
	  _ST("003 BBB CCC 003 d")
	  _ST("001 AAA @ @ @")
	  _P1("join_leftouterjoin -r 1=2 left.ssv right.ssv")
	  _ST("001 AAA @ @")
	  _ST("002 AAA AAA a")
	  _ST("003 BBB CCC c")
	  _ST("003 BBB CCC d")
	  _ST("001 AAA @ @")
	  _P1("join_leftouterjoin 1=2 2=1 left.ssv right.ssv")
	  _ST("001 AAA @ @ @")
	  _ST("002 AAA AAA 002 a")
	  _ST("003 BBB @ @ @")
	  _ST("001 AAA @ @ @")
	  _P1("join_leftouterjoin -r 1=2 2=1 left.ssv right.ssv")
	  _ST("001 AAA @")
	  _ST("002 AAA a")
	  _ST("003 BBB @")
	  _ST("001 AAA @")
	  _P1("") },

	TEXTSET_END
};
