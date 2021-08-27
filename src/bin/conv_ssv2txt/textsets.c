/*
 * Copyright (c) 2016,2017,2021 Daichi GOTO
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

	{ "command_copyright", "en_", "2016,2017 ONGS Inc."},

	{ "command_comment", "ja_JP",
	  "SSVデータをテキスト表データへ変換して出力" },

	{ "command_comment", "en_", 
	  "convert the SSV data to the TEXT data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " " "[" _OPT("t") "] "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "SSVデータをテキストデータへ変換して出力。ファイルの指\n"
	  "定がないか、-が指定されている場合には標準入力を使用。" },

	{ "command_description", "en_", 
	  "Convert the SSV data to the TEXT data. If " 
	  _ARG("file")" is a single\ndash (`-') or absent, it reads "
	  "from the standard input." },

	{ "command_options", "ja_JP", 
	  _OPT("t") "		テーブル形式にフォーマットして表示\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file")"\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("t") "		Print the data in the txt-table format.\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file")"\t	Specify the file." },

	{ "command_example", "en_", 
	  _P1("cat data1.ssv")
	  _ST("000001 EUROPEAN_PEAR \\@CHINA")
	  _ST("000002 FRENCH_BEAN \\@CHINA")
	  _ST("000003 @ JAPAN")
	  _P1("cat data2.ssv")
	  _ST("0 0 0 1 2")
	  _ST("0 0 0 2 3")
	  _ST("0 0 0 3 4")
	  _P1("cat data1.ssv |")
	  _P2("conv_ssv2txt - data2.ssv")
	  _ST("000001 EUROPEAN PEAR @CHINA")
	  _ST("000002 FRENCH BEAN @CHINA")
	  _ST("000003 JAPAN")
	  _ST("0 0 0 1 2")
	  _ST("0 0 0 2 3")
	  _ST("0 0 0 3 4")
	  _P1("cat data1.ssv |")
	  _P2("conv_ssv2txt -t - data2.ssv")
	  _ST("000001 EUROPEAN PEAR @CHINA")
	  _ST("000002   FRENCH BEAN @CHINA")
	  _ST("000003                JAPAN")
	  _ST("     0             0      0 1 2")
	  _ST("     0             0      0 2 3")
	  _ST("     0             0      0 3 4")
	  _P1("") },

	TEXTSET_END
};
