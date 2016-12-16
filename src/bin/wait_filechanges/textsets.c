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
	  "ファイルやディレクトリが変更されるまで待機" },

	{ "command_comment", "en_", 
	  "wait until the files or directories change" },

	{ "command_synopsis", "en_",
	  _CMD(CMDNAME) " "
	  "[" _OPT("phvD") "] [" _OPT("-") "] "
	  _ARG("file") "|" _ARG("dir") " "
	  "[" _ARG("file") "|" _ARG("dir") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  "ファイルやディレクトリに何らかの変更が発生するまで待機。ディ\n"
	  "レクトリが指定された場合には再帰的にファイルやディレクトリを\n"
	  "監視対象とする。" },

	{ "command_description", "en_", 
	  "Wait until the specified files or directories change. If one\n"
	  "or more directories are specified, watch the files and\n"
	  "directories recursively." },

	{ "command_options", "ja_JP", 
	  _OPT("p") "		監視対象を一覧で出力\n"
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("file") "\t	ファイルを指定\n"
	  _ARG("dir") "		ディレクトリを指定" },
	
	{ "command_options", "en_", 
	  _OPT("p") "		Print the monitoring files and directries.\n"
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("file") "\t	Specify the file.\n"
	  _ARG("dir") "		Specify the directory." },
	
	{ "command_example", "en_",
	  _P("while wait_filechanges .")
	  _P2("do")
	  _P2("	make clean")
	  _P2("	make")
	  _P2("	make test")
	  _P2("done")
	  _S("...")
	  _P("") },

	TEXTSET_END
};
