#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./sqlite3.h"
#include "./sql_manage.h"
#include "./manavis.h"

int main(void) {
  const char *database_file = "./database.db";
  sqlite3 *database = NULL;

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  const char *retrieve_statement =
    "SELECT * FROM Expense a, Income b, Exercise c Where a.Date = b.Date = c.Date;";
  open_database(database_file, &database);
  retrieve_data_from_database(retrieve_statement, database);

  manavis_show_window(window, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  sqlite3_close(database);
  return 0;
}
