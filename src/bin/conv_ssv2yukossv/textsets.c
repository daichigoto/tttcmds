/*
 * Copyright (c) 2019,2021 Daichi GOTO
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

	{ "command_copyright", "en_", "2019 ONGS Inc." },

	{ "command_comment", "ja_JP",
	  "SSVデータを有効SSVデータへ変換して出力" },

	{ "command_comment", "en_", 
	  "convert the SSV data to the Yuko SSV data" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("d") "] "
	  "[" _OPT("hvD") "] [" _OPT("-") "] "
	  "[" _ARG("file") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "SSVデータを有効SSVデータへ変換して出力。ファイルの指定が\n"
	  "ないか、-が指定されている場合には標準入力を使用。\n" 
	  "\n"
	  "処理できるSSVデータはUTF-8で次の形式である必要がある。\n"
	  "\n"
	  "	ID タイムスタンプ 任意 有効 任意 任意 任意 ...\n"
	  "\n"
	  "または\n"
	  "\n"
	  "	ID タイムスタンプ 任意 無効 任意 任意 任意 ...\n"
	  "\n"
	  "たとえば、次のようなデータが処理対象となる。\n"
	  "\n"
	  "	0000684184 20190809102300 @ 有効 12 @\n"
	  "	0000684184 20190809102309 @ 無効 0 @\n"
	  "	0000684179 20190809102333 @ 無効 0 @\n"
	  "	0000684184 20190809102341 @ 有効 31 @\n"
	  "	0000684184 20190809102610 @ 無効 0 有\n"
	  "	0000684179 20190809102629 @ 有効 7 有\n"
	  "	0000684179 20190809102323 @ 無効 0 @\n"
	  "	0000684190 20190809102633 @ 無効 0 有\n"
	  "	0000684190 20190809102629 @ 有効 56 有\n"
	  "	0000684192 20190809102634 @ 有効 55 有\n"
	  "\n"
	  "上記データであれば、1列目の値ごとにもっとも新しく、かつ、\n"
	  "4列目が\"有効\"であるデータが抽出される。\n"
	  "\n"
	  "	0000684179 20190809102629 @ 有効 7 有\n"
	  "	0000684192 20190809102634 @ 有効 55 有"
	},

	{ "command_description", "en_", 
	  "Convert the SSV data to the Yuko SSV data. If " 
	  _ARG("file")" is a\nsingle dash (`-') or absent, it reads "
	  "from the standard input.\n" 
	  "\n"
	  "The SSV data that can be processed must be in UTF-8 and in "
	  "the \nfollowing format.\n"
	  "\n"
	  "	ID timestamp any 有効 any any any ...\n"
	  "\n"
	  "または\n"
	  "\n"
	  "	ID timestamp any 無効 any any any ...\n"
	  "\n"
	  "For example, the following data can be processed.\n"
	  "\n"
	  "	0000684184 20190809102300 @ 有効 12 @\n"
	  "	0000684184 20190809102309 @ 無効 0 @\n"
	  "	0000684179 20190809102333 @ 無効 0 @\n"
	  "	0000684184 20190809102341 @ 有効 31 @\n"
	  "	0000684184 20190809102610 @ 無効 0 T\n"
	  "	0000684179 20190809102629 @ 有効 7 T\n"
	  "	0000684179 20190809102323 @ 無効 0 @\n"
	  "	0000684190 20190809102633 @ 無効 0 T\n"
	  "	0000684190 20190809102629 @ 有効 56 T\n"
	  "	0000684192 20190809102634 @ 有効 55 T\n"
	  "\n"
	  "For the above data, the latest data is extracted for each "
	  "ID\n""in the 1st column, and the data in the 4th column is "
	  "\"有効\".\n"
	  "\n"
	  "	0000684179 20190809102629 @ 有効 7 T\n"
	  "	0000684192 20190809102634 @ 有効 55 T"
	},

	{ "command_options", "ja_JP", 
	  _OPT("d") "		2列目、3列目、4列目を出力しない\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file")"\t	ファイルを指定" },
	
	{ "command_options", "en_", 
	  _OPT("d") "		Does not output the 2nd, 3rd, and 4th "
	  			"columns.\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file")"\t	Specify the file." },

	{ "command_example", "en_", 
	  _P1("cat data.ssv")
	  _ST("0000684184 20190809102300 @ 有効 12 @")
	  _ST("0000684184 20190809102309 @ 無効 0 @")
	  _ST("0000684179 20190809102333 @ 無効 0 @")
	  _ST("0000684184 20190809102341 @ 有効 31 @")
	  _ST("0000684184 20190809102610 @ 無効 0 有")
	  _ST("0000684179 20190809102629 @ 有効 7 有")
	  _ST("0000684179 20190809102323 @ 無効 0 @")
	  _ST("0000684190 20190809102633 @ 無効 0 有")
	  _ST("0000684190 20190809102629 @ 有効 56 有")
	  _ST("0000684192 20190809102634 @ 有効 55 有")
	  _P1("conv_ssv2yukossv data.ssv")
	  _ST("0000684179 20190809102629 @ 有効 7 有")
	  _ST("0000684192 20190809102634 @ 有効 55 有")
	  _P1("conv_ssv2yukossv -d data.ssv")
	  _ST("0000684179 7 有")
	  _ST("0000684192 55 有")
	  _P1("") },

	TEXTSET_END
};
