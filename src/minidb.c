#include "api.h"

//Schema:
//GROUP_SEP->END_TEXT = TableName
//END_TEXT->EOT = ColumnCount. Not atoi? Just use byte value? Limiting column number to size_t?

//DB be plain-text for now?
//Opinion: DBs should enforce types.

//Sample DB:
//29 65 3 65 31 66 31 30

int new_table(FILE* f, const char* name, size_t name_length, size_t columns) {
  // Go to end of file.
  while(1) {
    if(feof(f)){break;}
  }
  // Indicate new group
  fputc(GROUP_SEP, f);
  // Record group name
  for(size_t i = 0; i < name_length; i++) {
    fputc(name[i], f);
  }
  // Mark name end
  fputc(END_TEXT, f);
  // Record number of columns
  fputc(columns, f);
  // End record header
  fputc(EOT, f);

  return 1;
}

size_t count_tables(FILE* f) {
  size_t c = 0;
  size_t chr;
  size_t prev = 0;
  // Go to start of file.
  fseek(f, 0, SEEK_SET);
  while(1) {
    if(feof(f)){break;}
    // See if next char is interesting
    chr = fgetc(f);
    if(chr == GROUP_SEP && prev != ESC) {c++;}
    prev = chr;
  }
  // Finished, return to start of file.
  fseek(f, 0, SEEK_SET);

  //Fix counting.
  if(c != 0) {
    c++;
  }

  return c;
}

size_t count_records(FILE* f) {
  size_t c = 0;
  size_t chr;
  size_t prev = 0;
  // Go to start of file.
  fseek(f, 0, SEEK_SET);
  while(1) {
    if(feof(f)){break;}
    // See if next char is interesting
    chr = fgetc(f);
    if(chr == RECORD_SEP && prev != ESC) {c++;}
    prev = chr;
  }
  // Finished, return to start of file.
  fseek(f, 0, SEEK_SET);

  //Fix counting.
  if(c != 0) {
    c++;
  }


  return c;
}

int new_db(FILE* f) {
  // Write our 'MDB' header we
  // use to identify a DB.

  // Go to start of file.
  fseek(f, 0, SEEK_SET);
  fputc('M', f);
  fputc('D', f);
  fputc('B', f);
  // Go to start of file.
  fseek(f, 0, SEEK_SET);
  return 1;
}

int is_minidb(FILE* f) {
  // Check if the file has the 'MDB' header
  // we use to identify our DB.

  // Go to start of file.
  fseek(f, 0, SEEK_SET);
  char c = 0;
  c = fgetc(f);
  if(feof(f) || c != 'M'){return 0;}
  c = fgetc(f);
  if(feof(f) || c != 'D'){return 0;}
  c = fgetc(f);
  if(feof(f) || c != 'B'){return 0;}
  // Go to start of file.
  fseek(f, 0, SEEK_SET);
  return 1;
}

void stat(FILE* f) {
  int isdb = is_minidb(f);
  size_t tables = count_tables(f);
  size_t records = count_records(f);

  printf("%s\n", "File Statistics:");
  if(isdb) {
    printf("%s%zd\n", "Tables: ", tables);
    printf("%s%zd\n", "Records: ", records);
  }
  else {
    printf("%s\n", "Not a valid miniDB database file.");
  }
}

void cli_help() {
  printf("%s\n", "miniDB - Help");
  printf("%s%s - %zd\n", "Version: ", version, version_no);
}

int main(int argc, char* argv[]) {

  if(argc > 1) {
    // minidb help
    if(argc == 2) {
      // No need to check if arg is actually
      // 'help'. This is the only option that
      // would make sense anyway.
      cli_help();
    }
    else if(argc == 3) {
      // minidb new FILE
      if(argv[1][0] == 'n' &&
         argv[1][1] == 'e' &&
         argv[1][2] == 'w') {
        FILE* f = fopen(argv[2], "w");
        if(f == NULL) {
          fprintf(stderr, "%s\n", "Unable to create or open file. Do you have permission?");
          return 1;
        }
        new_db(f);
        fclose(f);
      }
      // minidb stat FILE
      else if(argv[1][0] == 's' &&
              argv[1][1] == 't' &&
              argv[1][2] == 'a' &&
              argv[1][3] == 't') {
        FILE* f = fopen(argv[2], "r");
        if(f == NULL) {
          fprintf(stderr, "%s\n", "Unable to open file for reading. Do you have permission? Does it exist?");
          return 1;
        }
        stat(f);
        fclose(f);
      }
      else {
        cli_help();
      }
    }
    // minidb modify FILE new table NAME COLUMNS
    // minidb modify FILE rename table NAME
    // minidb modify FILE resize table NAME COLUMNS
  } else {
    cli_help();
  }

}
