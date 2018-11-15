#ifndef MINIDB_API

#include <stdio.h>
#include <stdlib.h>

#define GROUP_SEP 29
#define RECORD_SEP 30
#define UNIT_SEP 31
#define ESC 27
#define END_TEXT 3
#define EOT 4
#define EMPTY_COLUMN 24

//Schema:
//GROUP_SEP->END_TEXT = TableName
//END_TEXT->EOT = ColumnCount. Not atoi? Just use byte value? Limiting column number to size_t?

//DB be plain-text for now?
//Opinion: DBs should enforce types.

//Sample DB:
//29 65 3 65 31 66 31 30

int new_table(FILE* f, const char* name, size_t name_length, size_t columns);

size_t count_tables(FILE* f);

size_t count_records(FILE* f);

int is_minidb(FILE* f);

void stat(FILE* f);

// Past Versions:
//
const char* version = "Silicon Dioxide"; //i.e. Sand. It's weak and crumbly.
const size_t version_no = 0;

void cli_help();

#define MINIDB_API
#endif
