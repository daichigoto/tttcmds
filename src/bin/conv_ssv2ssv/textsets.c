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
	  "SSVデータを正規SSVデータへ変換して出力" },

	{ "command_comment", "en_", 
	  "convert the SSV data to the normalized SSV data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
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
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file")"\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file")"\t	Specify the file." },

	{ "command_example", "en_", 
	  _P("cat data1.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("a b c d")
	  _S(" a b c d")
	  _P("conv_ssv2ssv data1.ssv")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("a b c d @ @ @ @ @")
	  _S("@ a b c d @ @ @ @")
	  _P("cat data2.ssv")
	  _S("A")
	  _S("B")
	  _P("conv_ssv2ssv data2.ssv data1.ssv")
	  _S("A @ @ @ @ @ @ @ @")
	  _S("B @ @ @ @ @ @ @ @")
	  _S("1 2 3 4 5 6 7 8 9")
	  _S("a b c d @ @ @ @ @")
	  _S("@ a b c d @ @ @ @")
	  _P("") },

	TEXTSET_END
};
