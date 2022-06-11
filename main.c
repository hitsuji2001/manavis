#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./sqlite3.h"
#include "./sql_manage.h"
#include "./calendar_view.h"
#include "./manavis.h"

int main(void) {
  const char *database_file = "./database.db";
  const char *statements_file = "./statement.sql";
  sqlite3 *database = NULL;

  /* SDL_Window *window = NULL; */
  /* SDL_Renderer *renderer = NULL; */

  open_database(database_file, &database);

  sqlh_reset_database_with_statements_file(statements_file, database);

  sqlh_print_all_database(database);

  /* mnv_show_window(window, renderer, WINDOW_WIDTH, WINDOW_HEIGHT); */

  /* SDL_DestroyWindow(window); */
  /* SDL_DestroyRenderer(renderer); */
  /* SDL_Quit(); */

  sqlite3_close(database);
  return 0;
}
