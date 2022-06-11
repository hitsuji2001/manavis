#include "./sql_manage.h"

int sqlh_default_callback(void *not_used, int argc, char **argv, char **az_col_name) {
  (void) not_used;
  for (int i = 0; i < argc; ++i) {
    if (argv[i] == NULL) continue;
    printf("%s = %s\n", az_col_name[i], argv[i]);
  }    
  printf("\n");

  return 0;
}

void sqlh_yank_all_statements_from_file(const char *file_path, sqlite3 *database) {
  FILE *file = fopen(file_path, "rb");
  char *buffer = NULL;
  char *line = NULL;
  uint64_t length;

  // Open file
  if (file == NULL) {
    fprintf(stderr, "Could not open file: %s, %s\n", file_path, strerror(errno));
    exit(1);
  } else {
    printf("Successfully open file: %s\n", file_path);
  }

  // Find the size of the file to allocate buffer
  if (fseek(file, 0, SEEK_END) < 0) {
    fprintf(stderr, "[ERROR]: Could not read file %s: %s\n", file_path, strerror(errno));
    fclose(file);
    exit(1);
  }
  length = ftell(file);
  if (fseek(file, 0, SEEK_SET) < 0) {
    fprintf(stderr, "[ERROR]: Could not read file %s: %s\n", file_path, strerror(errno));
    fclose(file);
    exit(1);
  }
  buffer = malloc(length);

  if (buffer == NULL) {
    fprintf(stderr, "[ERROR]: Could not allocate buffer\n");
    fclose(file);
    exit(1);
  }
  memset(buffer, 0, length);

  // Yank the content of the file to buffer
  while (getline(&line, &length, file) != -1) {
    if (line[0] == '-' && line[1] == '-') continue;
    else if (line[0] == '\n') continue;
    buffer = strcat(buffer, line);
  }
  fclose(file);

  if (line != NULL) free(line);
  if (buffer != NULL) {
    sqlh_add_records_to_database(buffer, database);
  }
}

void sqlh_reset_database(sqlite3 *database) {
  create_income_table(database);
  create_expense_table(database);
  create_exercise_table(database);
}

void sqlh_reset_database_with_statements_file(const char *file_path, sqlite3 *database) {
  sqlh_reset_database(database);
  sqlh_yank_all_statements_from_file(file_path, database);
}

void open_database(const char *file_path, sqlite3 **database) {
  int return_code;
  return_code = sqlite3_open(file_path, database);

  if (return_code != SQLITE_OK) {
    fprintf(stderr, "[ERROR]: Cannot open database: %s\n", sqlite3_errmsg(*database));
    sqlite3_close(*database);

    exit(1);
  } else {
    printf("Successfully open database!\n");
  }
}

void sqlh_add_records_to_database(const char *statement, sqlite3 *database) {
  int return_code;
  char *err_msg = 0;

  return_code = sqlite3_exec(database, statement, 0, 0, &err_msg);
  if (return_code != SQLITE_OK) {
    fprintf(stderr, "[ERROR]: Failed to add record(s): %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

void sqlh_retrieve_data_from_database(const char *statement, sqlite3 *database) {
  int return_code;
  char *err_msg = 0;

  return_code = sqlite3_exec(database, statement, sqlh_default_callback, 0, &err_msg);
  if (return_code != SQLITE_OK) {
    fprintf(stderr, "[ERROR]: Failed to retrieve data: %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

void sqlh_retrieve_data_from_database_with_callback(const char *statement, sqlite3 *database, int (*callback)(void *, int, char **, char **)) {
  int return_code;
  char *err_msg = 0;

  return_code = sqlite3_exec(database, statement, callback, 0, &err_msg);
  if (return_code != SQLITE_OK) {
    fprintf(stderr, "[ERROR]: Failed to retrieve data: %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

void sqlh_print_all_database(sqlite3 *database) {
  const char *statement =
    "SELECT * FROM Income;"
    "SELECT * FROM Expense;"
    "SELECT * FROM Exercise;";

  sqlh_retrieve_data_from_database(statement, database);
}

void create_income_table(sqlite3 *database) {
  int return_code;
  char *err_msg = 0;
 
   const char *statement =
    "DROP TABLE IF EXISTS Income;"
    "CREATE TABLE Income(Date DATE, Type VARCHAR(255), Income INTEGER, Category VARCHAR(255), Description VARCHAR(255), Note VARCHAR(255));";
  
  return_code = sqlite3_exec(database, statement, 0, 0, &err_msg);

  if (return_code != SQLITE_OK) {
    fprintf(stderr, "[ERROR]: Failed to create table: %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

void create_expense_table(sqlite3 *database) {
  int return_code;
  char *err_msg = 0;

  const char *statement =
    "DROP TABLE IF EXISTS Expense;"
    "CREATE TABLE Expense(Date DATE, Type VARCHAR(255), Expense INTEGER, Category VARCHAR(255), Description VARCHAR(255), Note VARCHAR(255));";
  
  return_code = sqlite3_exec(database, statement, 0, 0, &err_msg);

  if (return_code != SQLITE_OK) {
    fprintf(stderr, "[ERROR]: Failed to create table: %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

void create_exercise_table(sqlite3 *database) {
  int return_code;
  char *err_msg = 0;

  const char *statement =
    "DROP TABLE IF EXISTS Exercise;"
    "CREATE TABLE Exercise(Date DATE, Activity VARCHAR(255), Category VARCHAR(255), Note VARCHAR(255));";
  
  return_code = sqlite3_exec(database, statement, 0, 0, &err_msg);

  if (return_code != SQLITE_OK) {
    fprintf(stderr, "[ERROR]: Failed to create table: %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

