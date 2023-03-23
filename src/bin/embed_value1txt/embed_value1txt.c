/*
 * Copyright (c) 2016,2019,2021,2023 Daichi GOTO
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

static inline void print_dbt(DBT *);
static inline void println_dbt(DBT *);

int
main(int argc, char *argv[])
{
	getcmdargs(argc, argv, "hvD", 
	           CMDARGS_STDIN_TO_TMPFILE|
	           CMDARGS_R_NEED|
		   CMDARGS_R_ARGARG_1_NEED|
		   CMDARGS_R_ARGARG_2_NEED);

	/*
	 * setup the label and value sets
	 */
        DB *db;
        DBT key, val;

	// BD_BTREE cannot be used because the length of the key value 
	// is not fixed. You need to use BD_HASH.
	db = dbopen(NULL, O_CREAT | O_RDWR, 0, DB_HASH, NULL);

	for (int i = 0; i < R_ARGC; i++) {
		key.data = cmdargs.r_argv_arg1[i+1];
		key.size = strlen(key.data) + 1;
		val.data = cmdargs.r_argv_arg2[i+1];
		val.size = strlen(val.data) + 1;
		db->put(db, &key, &val, 0);
	}

	if (FLAG_D) {
		while (0 == db->seq(db, &key, &val, R_NEXT)) {
			print_dbt(&key);		
			println_dbt(&val);		
		}
	}

	FILEPROCESS_ALLBUFFER

	getcmdargs_unlinktmpf();

	exit(EX_OK);
}

static inline void
print_dbt(DBT *dbt_p)
{
        char buf[4096];
        int len = 0;

        if (4096 > dbt_p->size) {
                len = dbt_p->size;
        }
        else {
                len = 4096 - 1;
        }

        memcpy(buf, dbt_p->data, len);
        buf[len] = '\0';

        fprintf(stderr, "[%zu %s]", dbt_p->size, buf);
}

static inline void
println_dbt(DBT *dbt_p)
{
        print_dbt(dbt_p);
        fprintf(stderr, "\n");
}
