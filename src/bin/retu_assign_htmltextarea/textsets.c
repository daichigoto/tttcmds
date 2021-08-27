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

	{ "command_comment", "ja_JP",
	  "列をHTML TEXTAREAデータに変換する" },

	{ "command_comment", "en_",
	  "convert column to HTML TEXTAREA data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("r") "] "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N") "|" _ARG("N/M") " "
	  "[" _ARG("N") "|" _ARG("N/M") "|" 
	  _ARG("N._attr_.a.v") "|\n" _ARG("N/M._attr_.a.v")
	  " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "列の値をHTML TEXTAREAデータに変換する。\n"
	  "\n"
	  _ARG("N._attr_.a.v") "\t" _ARG("N") "列のTEXTAREA要素に"
	  	_ARG("v") "の値を指定した属性" _ARG("a") "を追加\n"
	  _ARG("N/M._attr_.a.v") "\t" _ARG("N._attr_.a.v") 
	  	"と同じ処理を" _ARG("M") "列まで適用\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Convert the values of specified columns to HTML TEXTAREA data.\n"
	  "\n"
	  _ARG("N._attr_.a.v") "\t" "Assign the attribution " _ARG("a")
	  	" that has the value " _ARG("v") " to\n\t\t"
		"the TEXTAREA element of the " _ARG("N") "th column.\n"
	  _ARG("N/M._attr_.a.v") "\t" "Process " _ARG("N") "th to " 
	  	_ARG("M") "th columns in the same way as\n\t\t"
		_ARG("N._attr_.a.v") ".\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it reads "
	  "from the\nstandard input." },

	{ "command_options", "ja_JP", 
	  _OPT("r") "		前の列の値を参照使用可能(\\1, \\2...)\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("r") "		Use references to the pre columns "
	  			"(\\1, \\2...)\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file." },
	
	{ "command_example", "en_", 
	  _P1("echo 1 @ | retu_assign_htmltextarea 1/2")
	  _ST("<textarea>1</textarea> <textarea></textarea>")
	  _P1("echo 1 @ |")
	  _P2("assign_htmltextarea \\")
	  _P2("\t1._attr_.name.nam1 \\")
	  _P2("\t2._attr_.name.'nam 2' \\")
	  _P2("\t2._attr_.id.uniq")
	  _ST("<textarea_name=\"nam1\">1</textarea> "
	     "<textarea_name=\"nam_2\"_id=\"uniq\">\n</textarea>")
	  _P1("echo '1 @ \\@ _ \\_ \" @' |")
	  _P2("retu_assign_htmltextarea -r \\")
	  _P2("\t7._attr_.name.nam7 \\")
	  _P2("\t7._attr_.id.'\\1:\\2:\\3:\\4:\\5:\\6'")
	  _ST("1 @ \\@ _ \\_ \" <textarea_name=\"nam7\"_"
	     "id=\"1::@:_:\\_:&quot;\"></textarea>")
	  _P1("") },

	TEXTSET_END
};
