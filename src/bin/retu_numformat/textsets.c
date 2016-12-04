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
	  "数値を変換して出力" },

	{ "command_comment", "en_",
	  "convert the format of number to another" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N.f") "|" _ARG("N/M.f") " "
	  "[" _ARG("N.f") "|" _ARG("N/M.f") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "指定した列の数値形式を変換して出力。\n"
	  "\n"
	  _ARG("N.f") "\t\t" _ARG("N") "列の数値データを読み込み、" 
	  	_ARG("f") "フォーマットに変換して\n\t\t出力する。"
		"フォーマットは ANSI X3.159-1989 および\n\t\t"
		"ISO/IEC 9899:1999に準拠\n"
	  _ARG("N/M.f") "\t\t" _ARG("N.f") "と同じ処理を" _ARG("M")
	  	"列まで適用\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Convert the format of specified column's number to the "
	  "another.\n"
	  "\n"
	  _ARG("N.f") "\t\tConvert the number of " _ARG("N") 
	  	"th column to another.\n\t\t" _ARG("f") " is the dst "
		"format based on ANSI X3.159-1989 and\n\t\t"
		"ISO/IEC 9899:1999.\n"
	  _ARG("N/M.f") "\t\tProcess " _ARG("N") "th to " _ARG("M")
		"th columns in the same way as\n\t\t" _ARG("N.f") ".\n"
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
	  _P("echo 1 2 3 4 5 6 7 8 9 | retu_numformat 1/5.'%06g'")
	  _S("000001 000002 000003 000004 000005 6 7 8 9")
	  _P("echo 1 2 3 4 5 6 7 8 9 | retu_numformat 1/3.'[ %06g ]'")
	  _S("[_000001_] [_000002_] [_000003_] 4 5 6 7 8 9")
	  _P("echo aa bb cc dd ee ff | retu_numformat 1/6.'%06g'")
	  _S("aa bb cc dd ee ff")
	  _P("echo 1 bb cc 3 ee ff | retu_numformat 1/6.'%06g'")
	  _S("000001 bb cc 000003 ee ff")
	  _P("") },

	TEXTSET_END
};
