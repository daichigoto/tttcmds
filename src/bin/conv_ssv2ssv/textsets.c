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

	{ "command_copyright", "en_", "2017 ONGS Inc." },

	{ "command_comment", "ja_JP",
	  "SSVデータを正規SSVデータへ変換して出力" },

	{ "command_comment", "en_", 
	  "convert the SSV data to the normalized SSV data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("n") "] "
	  "[" _OPT("w") " " _ARG("cols") "] "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "SSVデータを正規化されたSSVデータへ変換して出力。ファイルの指\n"
	  "定がないか、-が指定されている場合には標準入力を使用。" },

	{ "command_description", "en_", 
	  "Convert the SSV data to the normalized SSV data. If " 
	  _ARG("file")" is a\nsingle dash (`-') or absent, it reads "
	  "from the standard input." },

	{ "command_options", "ja_JP", 
	  _OPT("w") " " _ARG("cols") "\t\t指定した列数の後で折り返す\n"
	  _OPT("n") "		値に列番号を付けて表示\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file")"\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("w") " " _ARG("cols") "\t\tWrap lines after the "
	  			"specified column.\n"
	  _OPT("n") "		Number the output values of columns.\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file")"\t	Specify the file." },

	{ "command_example", "en_", 
	  _P1("cat data1.ssv")
	  _ST("1 2 3 4 5 6 7 8 9")
	  _ST("a b c d")
	  _ST(" a b c d")
	  _P1("conv_ssv2ssv data1.ssv")
	  _ST("1 2 3 4 5 6 7 8 9")
	  _ST("a b c d @ @ @ @ @")
	  _ST("@ a b c d @ @ @ @")
	  _P1("cat data2.ssv")
	  _ST("A")
	  _ST("B")
	  _P1("conv_ssv2ssv data2.ssv data1.ssv")
	  _ST("A @ @ @ @ @ @ @ @")
	  _ST("B @ @ @ @ @ @ @ @")
	  _ST("1 2 3 4 5 6 7 8 9")
	  _ST("a b c d @ @ @ @ @")
	  _ST("@ a b c d @ @ @ @")
	  _P1("conv_ssv2ssv -w 4 data1.ssv")
	  _ST("1 2 3 4")
	  _ST("5 6 7 8")
	  _ST("9 @ @ @")
	  _ST("a b c d")
	  _ST("@ a b c")
	  _ST("d @ @ @")
	  _P1("conv_ssv2ssv -n data1.ssv")
	  _ST("1:1 2:2 3:3 4:4 5:5 6:6 7:7 8:8 9:9")
	  _ST("1:a 2:b 3:c 4:d 5:@ 6:@ 7:@ 8:@ 9:@")
	  _ST("1:@ 2:a 3:b 4:c 5:d 6:@ 7:@ 8:@ 9:@")
	  _P1("") },

	TEXTSET_END
};
