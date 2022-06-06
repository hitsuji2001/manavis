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

void open_database(const char *file_path, sqlite3 **database) {
  int return_code;
  return_code = sqlite3_open(file_path, database);

  if (return_code != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*database));
    sqlite3_close(*database);

    exit(1);
  } else {
    printf("Successfully open database!\n");
  }
}

void create_income_table(sqlite3 *database) {
  int return_code;
  char *err_msg = 0;
 
   const char *statement =
    "DROP TABLE IF EXISTS Income;"
    "CREATE TABLE Income(Date DATE, Type VARCHAR(255), Income INTEGER, Category VARCHAR(255), Note VARCHAR(255));";
  
  return_code = sqlite3_exec(database, statement, 0, 0, &err_msg);

  if (return_code != SQLITE_OK) {
    fprintf(stderr, "Failed to create table: %s\n", err_msg);

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
    "CREATE TABLE Expense(Date DATE, Type VARCHAR(255), Expense INTEGER, Category VARCHAR(255), Note VARCHAR(255));";
  
  return_code = sqlite3_exec(database, statement, 0, 0, &err_msg);

  if (return_code != SQLITE_OK) {
    fprintf(stderr, "Failed to create table: %s\n", err_msg);

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
    fprintf(stderr, "Failed to create table: %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

void add_records_to_database(const char *statement, sqlite3 *database) {
  int return_code;
  char *err_msg = 0;

  return_code = sqlite3_exec(database, statement, 0, 0, &err_msg);
  if (return_code != SQLITE_OK) {
    fprintf(stderr, "Failed to add record(s): %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

void retrieve_data_from_database(const char *statement, sqlite3 *database) {
  int return_code;
  char *err_msg = 0;

  return_code = sqlite3_exec(database, statement, sqlh_default_callback, 0, &err_msg);
  if (return_code != SQLITE_OK) {
    fprintf(stderr, "Failed to retrieve data: %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

void retrieve_data_from_database_with_callback(const char *statement, sqlite3 *database, int (*callback)(void *, int, char **, char **)) {
  int return_code;
  char *err_msg = 0;

  return_code = sqlite3_exec(database, statement, callback, 0, &err_msg);
  if (return_code != SQLITE_OK) {
    fprintf(stderr, "Failed to retrieve data: %s\n", err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(database);

    exit(1);
  }
}

void reset_database(sqlite3 *database) {
  create_income_table(database);
  create_expense_table(database);
  create_exercise_table(database);
}
