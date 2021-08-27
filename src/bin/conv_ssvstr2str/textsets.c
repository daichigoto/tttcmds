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

	{ "command_comment",
	  "ja_JP", "SSV文字列を文字列へ変換して出力" },

	{ "command_comment", "en_",
	  "convert the SSV string to the string" },

	{ "command_synopsis", "en_",
	  _CMD(CMDNAME) " "
	  "[" _OPT("hvD") "] [" _OPT("-") "] " _ARG("ssvstr") " "
	  "[" _ARG("ssvstr") " " _ETC "]" },

	{ "command_description", "ja_JP", 
	  _ARG("ssvstr") "を文字列に変換して出力。" },

	{ "command_description", "en_", 
	  "Convert the " _ARG("ssvstr") " to the string." },

	{ "command_options", "ja_JP", 
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定\n"
	  _ARG("ssvstr") "\t	SSV文字列を指定" },
	
	{ "command_options", "en_", 
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options.\n"
	  _ARG("ssvstr") "\t	Specify the SSV string.\n" },
	
	{ "command_example", "en_", 
	  _P1("conv_ssvstr2str '@'")
	  _ST("")
	  _P1("conv_ssvstr2str '\\@' '\\@\\@' '\\\\@' 'a\\@b'")
	  _ST("@ @@ \\@ a@b")
	  _P1("conv_str2ssvstr ._. ,___,")
	  _ST(". . ,   ,")
	  _P1("conv_str2ssvstr '\\_' '\\_\\_\\_'")
	  _ST("_ ___")
	  _P1("conv_str2ssvstr 'a_b_\\@_\\_\\__c_' '@' '\\\\@'")
	  _ST("a b @ __ c   \\@")
	  _P1("") },

	TEXTSET_END
};
