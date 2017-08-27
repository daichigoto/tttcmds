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

	{ "command_copyright", "en_", "2017 ONGS Inc." },

	{ "command_comment", "ja_JP", "指定した列に指定した列を付け足す" },

	{ "command_comment", "en_", "append the Ath column to the Nth "
	  "column" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("d") " " _ARG("delim") " ] "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N.A") "|"_ARG("N/M.A") " "
	  "[" _ARG("N.A") "|"_ARG("N/M.A") "] "
	  "[" _ARG("file") " " _ETC "]" },
	
	{ "command_description", "ja_JP", 
	  "指定した列を指定した列へ付け足す。\n"
	  "\n"
	  _ARG("N.A") "\t\t" 	_ARG("A") "列目の値を" _ARG("N") "列目に"
	  			"付け足す\n"
	  _ARG("N/M.A") "\t\t" _ARG("N.A") "と同じ処理を" _ARG("M")
	 			"列まで適用\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Append the Ath column to the Nth column.\n"
	  "\n"
	  _ARG("N.A") "\t	Print the value of the " _ARG("N") "th "
	  			"column if it and " _ARG("k") "\n"
				"\t\tdon't match, or print " _ARG("s") ".\n"
	  _ARG("N/M.A") "\t	Process the " _ARG("N") "th to " _ARG("M")
	  			"th columns in the same way "
				"\n\t\tas " _ARG("N.A") ".\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it reads "
	  "from the\nstandard input." },

	{ "command_options", "ja_JP", 
	  _OPT("d") " " _ARG("delim") "\t区切り文字列を指定"
	                        "（デフォルトは''）\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("d") " " _ARG("delim") "\tUse " _ARG("delim")  
	  			"as the delimiter string "
				"(default is '')\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file." },

	{ "command_example", "en_", 
	  _P("cat data.ssv")
	  _S("1 2 3 @ 5 6 7 8 9")
	  _S("@ b c d e f @ h i")
	  _P("retu_append 1.2 data.ssv")
	  _S("12 2 3 @ 5 6 7 8 9")
	  _S("b b c d e f @ h i")
	  _P("retu_append 1.4 data.ssv")
	  _S("1 2 3 @ 5 6 7 8 9")
	  _S("d b c d e f @ h i")
	  _P("retu_append 1/8.9 data.ssv")
	  _S("19 29 39 9 59 69 79 89 9")
	  _S("i bi ci di ei fi i hi i")
	  _P("retu_append -d, 1/8.9 data.ssv")
	  _S("1,9 2,9 3,9 9 5,9 6,9 7,9 8,9 9")
	  _S("i b,i c,i d,i e,i f,i i h,i i")
	  _P("") },

	TEXTSET_END
};
