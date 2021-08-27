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

	{ "command_copyright", "en_", "2016,2017 ONGS Inc." },

	{ "command_comment",
	  "ja_JP", "HTMLフォームデータをSSVデータへ変換して出力" },

	{ "command_comment", "en_",
	  "convert the HTML form data to the SSV data" },

	{ "command_synopsis", "en_",
	  _CMD(CMDNAME) " "
	  "[" _OPT("hvD") "] [" _OPT("-") "]" },

	{ "command_description", "ja_JP", 
	  "HTMLフォームデータをSSVデータへ変換して出力。" },

	{ "command_description", "en_", 
	  "Convert the HTML form data to the SSV data." },

	{ "command_options", "ja_JP", 
	  _OPT("h") "		使い方表示\n"
	  _OPT("v") "		バージョン表示\n"
	  _OPT("D") "		デバッグモード\n"
	  _OPT("-") "		オプションの終了を指定" },
	
	{ "command_options", "en_", 
	  _OPT("h") "		Print the usage message.\n"
	  _OPT("v") "		Print the version.\n"
	  _OPT("D") "		Enable the debug mode.\n"
	  _OPT("-") "		Specify the end of options." }, 

	{ "command_environment", "ja_JP", 
	  _ARG("conv_form2ssv") "は次の環境変数の影響を受ける。\n"
	  "\n"
	  "REQUEST_METHOD\tHTTPリクエスト方式を指定。POSTまたはGET\n"
	  "QUERY_STRING\tREQUEST_METHODがGETのとき\n"
	  "\t\tapplication/x-www-form-urlencodedのデータを保持\n" 
 	  "CONTENT_TYPE\tREQUEST_METHODがPOSTのときのデータ形式。次の"
	  "形式\n\t\tに対応\n"
	  "\n"
	  "\t\tapplication/x-www-form-urlencoded\n"
	  "\t\tmultipart/form-data\n"
	  "\n" 
	  "CONTENT_LENGTH\tREQUEST_METHODがPOSTのときのデータの長さ\n" },

	{ "command_environment", "en_", 
	  "The following environment variables affect the execution of\n"
	  _ARG("conv_form2ssv") ".\n"
	  "\n"
	  "REQUEST_METHOD\tHTTP Request method (POST or GET).\n"
	  "QUERY_STRING\tHTTP form data as "
	  "application/x-www-form-urlencoded\n\t\tif REQUEST_METHOD is "
	  "GET.\n" 
 	  "CONTENT_TYPE\tFormat of the HTTP form if REQUEST_METHOD is "
	  "POST. \n\t\tSupported formats are following:\n"
	  "\n"
	  "\t\tapplication/x-www-form-urlencoded\n"
	  "\t\tmultipart/form-data\n"
	  "\n" 
	  "CONTENT_LENGTH\tLength of the HTTP form if REQUEST_METHOD is "
	  "POST.\n" },

	{ "command_example", "en_", 
	  _P1("cat program.cgi")
	  _ST("#!/bin/sh")
	  _ST("")
	  _ST("conv_form2ssv > /tmp/form.ssv")
	  _ST("cat<<EOF")
	  _ST("<html>")
	  _ST("<body>")
	  _ST(" <table>")
	  _ST("  <tbody>")
	  _ST("   <tr>")
	  _ST("    <th>ID</th>")
	  _ST("    <th>CONTENT</th>")
	  _ST("   </tr>")
	  _ST("   <tr>")
	  _ST("    <td>$(gyosel 1=ID      /tmp/form.ssv | retusel 2)</td>")
	  _ST("    <td>$(gyosel 1=CONTENT /tmp/form.ssv | retusel 2)</td>")
	  _ST("   </tr>")
	  _ST("  </tbody>")
	  _ST("</table>")
	  _ST("</body>")
	  _ST("</html>")
	  _ST("EOF")
	  _ST("")
	  _ST("rm /tmp/form.ssv")
	  _P1("") },

	TEXTSET_END
};
