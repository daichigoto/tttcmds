/*
 * Copyright (c) 2016,2021 Daichi GOTO
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
	  "テキストファイルをテキストデータに組み込み出力" },

	{ "command_comment", "en_",
	  "embed text files into text data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("n") "] [" _OPT("hvD") "] [" _OPT("-") "] "
	  _ARG("N.l.f") " " "[" _ARG("N.l.f") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "指定したテキストファイルをテキストデータに組み込み、標準出力へ\n"
	  "出力する。\n"
	  "\n"
	  _ARG("N.l.f") "\t\t" "テキストデータ中の文字列" _ARG("l") "を"
	  	"テキストファイル" _ARG("f") "の\n\t\t中身に変換する\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Embed the specified text files into the text data and print to\n"
	  "the standard out.\n"
	  "\n"
	  _ARG("N.l.f") "\t\t" "Swap the label " _ARG("l") " in the text "
	  	"data for the\n\t\tcontent of the specified file " 
		_ARG("f") ".\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it reads "
	  "from the\nstandard input." },

	{ "command_options", "ja_JP", 
	  _OPT("n") "		ファイル" _ARG("f") "のEOF前の\\nを出力"
	  			"しない\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("n") "		Do not print the \\n before EOF of the "
	  			"file "_ARG("f") ".\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file." },
	
	{ "command_example", "en_", 
	  _P1("cat main.html")
	  _ST("<html>")
	  _ST("<body>")
	  _ST("	<thead>")
	  _ST("		<!--HEAD-->")
	  _ST("	</thead>")
	  _ST("	<tbody>")
	  _ST("		<!--BODY-->")
	  _ST("	</tbody>")
	  _ST("</body>")
	  _ST("</html>")
	  _P1("cat thead.html")
	  _ST("<tr><th>NAME1</th><th>NAME2</th><th>NAME3</th></tr>")
	  _P1("cat tbody.html")
	  _ST("<tr><td>a</td><td>b</td><td>c</td></tr>")
	  _P1("cat main.html |")
	  _P1("embed_txt1txt -n \\")
	  _P2("	1,'<!--HEAD-->',thead.html 2,'<!--BODY-->',tbody.html")
	  _ST("<html>")
	  _ST("<body>")
	  _ST("	<thead>")
	  _ST("		<tr><th>NAME1</th><th>NAME2</th><th>NAME3</th></tr>")
	  _ST("	</thead>")
	  _ST("	<tbody>")
	  _ST("		<tr><td>a</td><td>b</td><td>c</td></tr>")
	  _ST("	</tbody>")
	  _ST("</body>")
	  _ST("</html>")
	  _P1("") },

	TEXTSET_END
};
