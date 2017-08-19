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

	{ "command_comment", "ja_JP", "年月日の差分を求める" },

	{ "command_copyright", "en_", "2017 ONGS Inc." },

	{ "command_comment", "en_", 
	  "Calculate difference between two dates" },

	{ "command_synopsis", "en_",
	  _CMD(CMDNAME) " "
	  "[-f fmt] [-s] "
	  "[" _OPT("hvD") "] [--] date_B date_A" },

	{ "command_description", "ja_JP", 
	  "date_Aからdate_Bを引いた差分を日数で表示する。" },

	{ "command_description", "en_", 
	  "Subtract the date_B from date_A and output in days." },

	{ "command_options", "ja_JP", 
	  _OPT("f") " fmt	\tdate_Aおよびdate_Bのフォーマットを指定\n"
	            "		(既定値: %Y%m%d)\n"
	  _OPT("s") "		差分を秒数で出力\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定" },
	
	{ "command_options", "en_", 
	  _OPT("f") " fmt	\tSpecify a format of the date_A and "
	                       "the date_B\n"
	            "		(default: %Y%m%d).\n"
	  _OPT("s") "		Output in seconds.\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options." },
	
	{ "command_example", "en_",
	  _P("calc_subtract_date 20190225 20190225")
	  _S("0")
	  _P("calc_subtract_date 20190225 20190302")
	  _S("5")
	  _P("calc_subtract_date 20190302 20190225")
	  _S("-5")
	  _P("calc_subtract_date 20200225 20200302")
	  _S("6")
	  _P("calc_subtract_date 20200302 20200225")
	  _S("-6")
	  _P("calc_subtract_date -f %m-%d-%Y 02-25-2019 02-25-2019")
	  _S("0")
	  _P("calc_subtract_date -f %Y/%m/%d 2019/02/25 2019/03/02")
	  _S("5")
	  _P("calc_subtract_date -s 20190225 20190225")
	  _S("0")
	  _P("calc_subtract_date -s 20190225 20190302")
	  _S("432000")
	  _P("calc_subtract_date -s 20200225 20200302")
	  _S("518400")
	  _P("") },

	TEXTSET_END
};
