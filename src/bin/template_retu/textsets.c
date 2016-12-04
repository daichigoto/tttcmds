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

	{ "command_comment", "ja_JP", 
	  "retu系コマンド向けテンプレートコマンド" },

	{ "command_comment", "en_", 
	  "a template command for retu related commands" },

	{ "command_synopsis", "en_",
	  _CMD(CMDNAME) " "
	  "[" _OPT("a..zA..Z0..9@") "] [" _OPT("-") "] "
	  "[" _ARG("N") "|" _ARG("N.a1") "|" _ARG("N.a1.a2") "|\n"
	      _ARG("N.a1.a2.a3") "|" _ARG("N/M.a1") "|"
	      _ARG("N/M.a1.a2") "|" _ARG("N/M.a1.a2.a3") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]"	},

	{ "command_description", "ja_JP", 
	  "retu系コマンドのテンプレートコマンド。ファイルの指定がない\n"
	  "か、-が指定されている場合には標準入力を使用。" },

	{ "command_description", "en_", 
	  "A template command for retu related commands. If " _ARG("file")
	  " is a\nsingle dash (`-') or absent, it reads from the standard "
	  "input." },

	{ "command_options", "ja_JP",
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("N") "		" _ARG("N") "列目を指定\n"
	  _ARG("N.a1") "\t	" _ARG("N") "列目と列引数を1つ指定\n"
	  _ARG("N.a1.a2") "\t	" _ARG("N") "列目と列引数を2つ指定\n"
	  _ARG("N.a1.a2.a3") "	" _ARG("N") "列目と列引数を3つ指定\n"
	  _ARG("N/M") "\t	" _ARG("N") "列目から" _ARG("M")
	  			"列目を指定\n"
	  _ARG("N/M.a1") "\t	" _ARG("N") "列目から" _ARG("M")
	  			"列目を指定と列引数を1つ指定\n"
	  _ARG("N/M.a1.a2") "	" _ARG("N") "列目から" _ARG("M")
	  			"列目を指定と列引数を2つ指定\n"
	  _ARG("N/M.a1.a2.a3") "\t" _ARG("N") "列目から" _ARG("M")
	  			"列目を指定と列引数を3つ指定\n"
	  _ARG("file") "\t	ファイルを指定"	},

	{ "command_options", "en_",
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("N") "		Specify the " _ARG("N") "th column.\n"
	  _ARG("N.a1") "\t	Specify the " _ARG("N") "th column with "
	  			"an argument.\n"
	  _ARG("N.a1.a2") "\t	Specify the " _ARG("N") "th column with "
	  			"two arguments.\n"
	  _ARG("N.a1.a2.a3") "	Specify the " _ARG("N") "th column with "
	  			"three arguments.\n"
	  _ARG("N/M") "		Specify the range from the " _ARG("N")
	  			"th to " _ARG("M") "th column.\n"
	  _ARG("N/M.a1") "\t	Specify the range from the " _ARG("N")
	  			"th to " _ARG("M") "th column\n\t\t"
				"with a argument for each column.\n"
	  _ARG("N/M.a1.a2") "	Specify the range from the " _ARG("N")
	  			"th to " _ARG("M") "th column\n\t\t"
				"with two arguments for each column.\n"
	  _ARG("N/M.a1.a2.a3") "\tSpecify the range from the " _ARG("N")
	  			"th to " _ARG("M") "th column\n\t\t"
				"with three arguments for each column.\n"
	  _ARG("file") "\t	Specify the file." },

	TEXTSET_END
};
