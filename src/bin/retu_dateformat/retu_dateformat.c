/*
 * Copyright (c) 2017-2019,2021 Daichi GOTO
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

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "3:ehvD",
	           CMDARGS_R_NEED|
		   CMDARGS_R_ARGARG_1_NEED|
		   CMDARGS_R_ARGARG_2_NEED);

	/*
	 * Column number used as comparison basis for 30 hours
	 */
	int index_30hbase = 0;
	if (FLAG_3) {
		errno = 0;
		index_30hbase = (int)strtol(FLAG_3_ARG, (char **)NULL, 10);
                if (EINVAL == errno)
                        usage();
	}
	if (FLAG_D) {
		fprintf(stderr, "index_30hbase: %d\n", index_30hbase);
	}

	int str_len, ssvstr_len, outfmt_len, index, indexH, 
		hours30_output = 0, H, loopend = 0;
	char *str, *ssvstr, *p, *ptr, *ptr2, *p_base, 
		basedate[9], tgtdate[9], tgtH[3], varry[4] = "+0d";

	// time_t is a data type that holds the system time, defined in ISO C 
	// as a numeric type. It is defined as a numeric type in ISO C. On UNIX
	// and POSIX compatible systems, it holds a signed integer starting 
	// at 0:0:0 on January 1, 1970. The value of time_t can be obtained by 
	// the time() function.
	time_t tval;

	// struct tm is a structure that holds time data element by element.
	// struct tm {
	//   int   tm_sec;	second 0-60(C99) 0-61(C89) including leap secs
	//   int   tm_min;	minute 0-59
	//   int   tm_hour;	hour   0-23
	//   int   tm_mday;	day    1-31
	//   int   tm_mon;	month  0-11
	//   int   tm_year;	year   years from 1900
	//   int   tm_wday;	week   0-6 from Sunday
	//   int   tm_yday;     days   0-365 days from 1/1
	//   int   tm_isdst;    summer time flag +,0,- (0 meas no summer time)
	// }
	struct tm tm;
	struct tm tm_tomorrow;
	struct vary *v = NULL;

	// Set the date and time output (LC_TIME) to be processed according 
	// to the environment variables of the execution environment.
	(void) setlocale(LC_TIME, "");

	// Get current system time. The value of time_t can be obtained by 
	// the time() function.
	time(&tval);

	// Converts the time data in time_t to the time data of the execution 
	// environment's time zone and returns it as a struct tm.
	tm = *localtime(&tval);

	// strptime reads the string of the first argument as a time according 
	// to the format of the second argument, and stores it in structtm of 
	// the third argument.
	// Here, the current time is stored as the base data of struct tm.
	strptime("000000", "%H%M%S", &tm);
	tm_tomorrow = tm;

	str_len = ssvstr_len = BUFFER_SIZE;
	str = calloc(str_len, sizeof(char));
	ssvstr = calloc(ssvstr_len, sizeof(char));

	FILEPROCESS_GYO

	exit(EX_OK);
}
