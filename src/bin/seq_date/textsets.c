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

	{ "command_comment", "ja_JP", "ひと続きの日付データを出力" },

	{ "command_comment", "en_", "print sequences of dates" },

	{ "command_synopsis", "en_", 
	  _CMD(CMDNAME) " "
	  "[" _OPT("c") " " _ARG("count") "] "
	  "[" _OPT("i") " " _ARG("in_fmt") "] "
	  "[" _OPT("o") " " _ARG("out_fmt") "] "
	  "[" _OPT("V") " " _ARG("val") "] "
	  "[" _OPT("hvD") "] [" _OPT("-") "]\n"
	  _ARG("first") " [" _ARG("last") "]" },

	{ "command_description", "ja_JP", 
	  _ARG("first") "から" _ARG("last") "までの連続する日付データを"
	  "出力する。" },

	{ "command_description", "en_", 
	  "Print a sequence of dates from " _ARG("first") " to near "
	  _ARG("last") " as possible\nin increments or decrements of "
	  _ARG("val") ", one per line." },

	{ "command_options", "ja_JP", 
	  _OPT("c") " " _ARG("count") "\t出力する回数を指定\n"
	  _OPT("i") " " _ARG("in_fmt") "\t指定する日付データの形式\n"
	  _OPT("o") " " _ARG("out_fmt") "\t出力日付データの形式\n"
	  _OPT("V") " " _ARG("val")
	  			"\t\t増加分または減少分を"
				"[+-][0-9]+[SMHdwmy]で指定\n"
				"\t\t+\t増加\n"
				"\t\t-\t減少\n"
				"\t\ty\t年\n"
				"\t\tm\t月\n"
				"\t\tw\t週\n"
				"\t\td\t日\n"
				"\t\tH\t時\n"
				"\t\tM\t分\n"
				"\t\tS\t秒\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("first") "\t	開始日付データ\n" 
	  _ARG("last") "\t	終了日付データ" },
	 
	{ "command_options", "en_", 
	  _OPT("c") " " _ARG("count") 
	  			"\tSet the number of output count.\n"
	  _OPT("i") " " _ARG("in_fmt") 
	  			"\tSet the format of the input date.\n"
	  _OPT("o") " " _ARG("out_fmt") 
	  			"\tSet the format of the output date.\n"
	  _OPT("V") " " _ARG("val") 
	  			"\t\tSet the increase or decrease date by\n"
				"\t\t[+-][0-9]+[SMHdwmy].\n"
				"\t\t+\tincrements\n"
				"\t\t-\tdecrements\n"
				"\t\ty\tyear\n"
				"\t\tm\tmonth\n"
				"\t\tw\tweek\n"
				"\t\td\tday\n"
				"\t\tH\thour\n"
				"\t\tM\tminit\n"
				"\t\tS\tsecond\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("first") "\t	Specify the first date.\n" 
	  _ARG("last") "\t	Specify the last date." },

	{ "command_example", "en_", 
	  _P1("seq_date -i %Y%m%d -o %Y%m%d -V+1d 20170101 20170105")
	  _ST("20170101")
	  _ST("20170102")
	  _ST("20170103")
	  _ST("20170104")
	  _ST("20170105")
	  _P1("seq_date -i %Y%m -o %Y%m -V+2m 201701 201707")
	  _ST("201701")
	  _ST("201703")
	  _ST("201705")
	  _ST("201707")
	  _P1("seq_date -i %Y%m%d -o %Y%m%d -V-7d 20170130 20170101")
	  _ST("20170130")
	  _ST("20170123")
	  _ST("20170116")
	  _ST("20170109")
	  _ST("20170102")
	  _P1("seq_date -c 7 -i %Y%m%d -o %Y%m%d -V+7d 20170101")
	  _ST("20170101")
	  _ST("20170108")
	  _ST("20170115")
	  _ST("20170122")
	  _ST("20170129")
	  _ST("20170205")
	  _ST("20170212")
	  _P1("seq_date -c 7 -i %Y%m%d -o %Y%m%d -V-7d 20170101")
	  _ST("20170101")
	  _ST("20161225")
	  _ST("20161218")
	  _ST("20161211")
	  _ST("20161204")
	  _ST("20161127")
	  _ST("20161120")
	  _P1("") },

	TEXTSET_END
};
