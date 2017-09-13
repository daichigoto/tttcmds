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

	{ "command_comment", "ja_JP",
	  "文字列をフォーマット指定して出力" },

	{ "command_comment", "en_",
	  "convert the string to another format" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N.f") "|" _ARG("N/M.f") " "
	  "[" _ARG("N.f") "|" _ARG("N/M.f") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "文字列をフォーマット指定して出力。\n"
	  "\n"
	  _ARG("N.f") "\t\t" _ARG("N") "列の文字列を読み込み、" 
	  	_ARG("f") "フォーマットに変換して\n\t\t出力する。"
		"フォーマットはsnprintf(3)に準拠\n"
	  _ARG("N/M.f") "\t\t" _ARG("N.f") "と同じ処理を" _ARG("M")
	  	"列まで適用\n"
	  "\n"
	  "フォーマットはsnprintf(3)に準拠するほか、次の拡張指定に対応。\n"
	  "\n"
	  _ARG("%h") "\t\t文字列。ただし、HTML5属性値として指定できる\n"
	             "\t\tように空白、<、>、'、\"、`、=はHTML5エンティ\n"
		     "\t\tティ名に変換\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Convert the string of specified column to the another.\n"
	  "\n"
	  _ARG("N.f") "\t\tConvert the string of " _ARG("N") 
	  	"th column to another.\n\t\t" _ARG("f") " is the dst "
		"format based on snprintf(3)\n"
	  _ARG("N/M.f") "\t\tProcess " _ARG("N") "th to " _ARG("M")
		"th columns in the same way as\n\t\t" _ARG("N.f") ".\n"
	  "\n"
	  "The format conforms to snprintf(3) and some extensions as "
	  "follows:\n"
	  "\n"
	  _ARG("%h") "		A string will be converted to HTML5 "
	  			"attribute\n\t\tvalue (<, >, ', \", `, "
				"= and space will be\n\t\tconverted to "
				"HTML5 Entity Name).\n"
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
	  _P("echo aa bb cc dd | retu_strformat 2.'<p>DATA: %s</p>'")
	  _S("aa <p>DATA:_bb</p> cc dd")
	  _P("echo aa bb cc dd | retu_strformat 1/4.'<p>%s</p>'")
	  _S("<p>aa</p> <p>bb</p> <p>cc</p> <p>dd</p>")
	  _P("cat data.ssv")
	  _S("_<>'\"`= @ @")
	  _P("retu_strformat 1.'<input value=\"%s\">' data.ssv")
	  _S("<input_value=\"_<>'\"`=\"> @ @")
	  _P("retu_strformat 1.'<input value=\"%h\">' data.ssv")
	  _S("<input_value=\"&nbsp;&lt;&gt;&apos;&quot;&grave;&equals;\"> "
	     "@ @")
	  _P("") },

	TEXTSET_END
};
