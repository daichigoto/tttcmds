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

	{ "command_copyright", "en_", "2016,2017 ONGS Inc." },

	{ "command_comment", "ja_JP",
	  "SSVデータをテキストデータに組み込み出力" },

	{ "command_comment", "en_",
	  "embed ssv data into text data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  _OPT("t") " " _ARG("txtfile") " " 
	  "[" _OPT("s") " " _ARG("s.ssv") "] "
	  "[" _OPT("m") " " _ARG("max") "] "
	  "[" _OPT("n") "] [" _OPT("hvD") "] [" _OPT("-") "]\n"
	  _ARG("N.l") " " 
	  "[" _ARG("N.l") " " _ETC "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "指定したSSVデータをテキストデータに組み込み、標準出力へ"
	  "出力する。\n"
	  "\n"
	  _ARG("txtfile") "\t\t" "テキストファイルを指定\n"
	  _ARG("N.l") "\t\t" "テキストデータ中の文字列" _ARG("l") "を"
	  	"SSVデータの" _ARG("N") "列目の\n\t\t中身に変換する\n"
	  _ARG("s.ssv") "\t\t" "引数で" _ARG("N.l") "を指定する"
	  	"代わりに" _ARG("N l") "といった置換規則が\n"
		"\t\t書き込まれたSSVファイルを指定\n"
	  "\n"
	  "ファイルの指定がないか、-が指定されている場合には標準入力を"
	  "使用。" },

	{ "command_description", "en_", 
	  "Embed the specified ssv data into the text data and print to\n"
	  "the standard out.\n"
	  "\n"
	  _ARG("txtfile") "\t\t" "Specify the text file.\n"
	  _ARG("N.l") "\t\t" "Swap the label " _ARG("l") " in the text "
	  	"data for the\n\t\tcontent of the " 
		_ARG("N") "th column of the ssv data.\n"
	  _ARG("s.ssv") "\t\t" "Specify a ssv file including some "
	  	"swap rules\n\t\tlike "_ARG("N l") " instead of " 
		_ARG("N.l") " specification\n\t\ton the command line.\n"
	  "\n"
	  "If " _ARG("file") " is a single dash (`-') or absent, it reads "
	  "from the\nstandard input." },

	{ "command_options", "ja_JP", 
	  _OPT("t") " " _ARG("txtfile") "\tテキストデータファイルを指定(必須)\n" 
	  _OPT("s") " " _ARG("s.ssv") "\tSSV置換規則ファイルを指定\n" 
	  _OPT("m") " " _ARG("max") "\tSSV最大置換回数を指定\n" 
	  _OPT("n") "		" _ARG("txtfile") "のEOF前の\\nを出力しない\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("t") " " _ARG("txtfile") "\tSpecify the text data file (REQUIRED).\n"
	  _OPT("s") " " _ARG("s.ssv") "\tSpecify the swap-rules ssv file.\n"
	  _OPT("m") " " _ARG("max") "\tSpecify the number of maxium swap times.\n"
	  _OPT("n") "		Do not print the \\n before EOF of the "
				_ARG("txtfile") ".\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file." },
	
	{ "command_example", "en_", 
	  _P("cat main.html")
	  _S("<html>")
	  _S("<body>")
	  _S("	<h1><!--HEADER--></h1>")
	  _S("	<p><!--CONTENT--></p>")
	  _S("</body>")
	  _S("</html>")
	  _P("cat data.ssv")
	  _S("TITLE HELLO_WORLD!")
	  _P("embed_ssv1txt -t main.html \\")
	  _P2("	1:'<!--HEADER-->' 2:'<!--CONTENT-->' data.ssv")
	  _S("<html>")
	  _S("<body>")
	  _S("	<h1>TITLE</h1>")
	  _S("	<p>CONTENT</p>")
	  _S("</body>")
	  _S("</html>")
	  _P("cat table_bodytr.html")
	  _S("  <tr><td><!--L1--></td><td><!--L2--></td><td><!--L3--></td></tr>")
	  _P("cat farm.ssv")
	  _S("000001 CHINA U.S.")
	  _S("000002 JAPAN U.K.")
	  _S("000003 INDIA PHILIPPINES")
	  _S("000004 U.S. CANADA")
	  _S("000005 CHINA TURKEY")
	  _P("embed_ssv1txt -t table_bodytr.html \\")
	  _P2("	1:'<!--L1-->' 2:'<!--L2-->' 3:'<!--L3-->' farm.ssv")
	  _S("  <tr><td>000001</td><td>CHINA</td><td>U.S.</td></tr>")
	  _S("  <tr><td>000002</td><td>JAPAN</td><td>U.K.</td></tr>")
	  _S("  <tr><td>000003</td><td>INDIA</td><td>PHILIPPINES</td></tr>")
	  _S("  <tr><td>000004</td><td>U.S.</td><td>CANADA</td></tr>")
	  _S("  <tr><td>000005</td><td>CHINA</td><td>TURKEY</td></tr>")
	  _P("cat swap.ssv")
	  _S("3 <!--L3-->")
	  _S("1 <!--L1-->")
	  _S("2 <!--L2-->")
	  _P("embed_ssv1txt -t table_bodytr.html -s swap.ssv farm.ssv")
	  _S("  <tr><td>000001</td><td>CHINA</td><td>U.S.</td></tr>")
	  _S("  <tr><td>000002</td><td>JAPAN</td><td>U.K.</td></tr>")
	  _S("  <tr><td>000003</td><td>INDIA</td><td>PHILIPPINES</td></tr>")
	  _S("  <tr><td>000004</td><td>U.S.</td><td>CANADA</td></tr>")
	  _S("  <tr><td>000005</td><td>CHINA</td><td>TURKEY</td></tr>")
	  _P("embed_ssv1txt -t table_bodytr.html -s swap.ssv -m 2 farm.ssv")
	  _S("  <tr><td>000001</td><td><!--L2--></td><td>U.S.</td></tr>")
	  _S("  <tr><td>000002</td><td><!--L2--></td><td>U.K.</td></tr>")
	  _S("  <tr><td>000003</td><td><!--L2--></td><td>PHILIPPINES</td></tr>")
	  _S("  <tr><td>000004</td><td><!--L2--></td><td>CANADA</td></tr>")
	  _S("  <tr><td>000005</td><td><!--L2--></td><td>TURKEY</td></tr>")
	  _P("") },

	TEXTSET_END
};
