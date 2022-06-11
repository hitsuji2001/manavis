#ifndef __SQL_MANAGE_H__
#define __SQL_MANAGE_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include "./sqlite3.h"

int sqlh_default_callback(void *not_used, int argc, char **argv, char **az_col_name);
void sqlh_yank_all_statements_from_file(const char *file_path, sqlite3 *database);

void sqlh_reset_database(sqlite3 *database);
void sqlh_reset_database_with_statements_file(const char *file_path, sqlite3 *database);

void sqlh_add_records_to_database(const char *statement, sqlite3 *database);
void sqlh_retrieve_data_from_database(const char *statement, sqlite3 *database);
void sqlh_retrieve_data_from_database_with_callback(const char *statement, sqlite3 *database, int (*callback)(void *, int, char **, char **));

void sqlh_print_all_database(sqlite3 *database);

void open_database(const char *file_path, sqlite3 **database);

void create_income_table(sqlite3 *database);
void create_expense_table(sqlite3 *database);
void create_exercise_table(sqlite3 *database);


#endif // __SQL_MANAGE_H__
