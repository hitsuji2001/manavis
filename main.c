#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "./sqlite3.h"
#include "./sql_manage.h"

int main(void) {
  const char *database_file = "./database.db";

  sqlite3 *database = NULL;

  const char *expense_statement =
    "INSERT INTO Expense(Date, Expense, Category, Note) VALUES('2022/05/28', 500000, 'Food', 'Tiền cọc ăn lẩu');"
    "INSERT INTO Expense(Date, Expense, Category, Note) VALUES('2022/05/29', 170000, 'Food', 'Ăn lẩu');"
    "INSERT INTO Expense(Date, Expense, Category, Note) VALUES('2022/05/29', 50000, 'Gift', 'Nạp tiền điện thoại cho mẹ');"
    "INSERT INTO Expense(Date, Expense, Category, Note) VALUES('2022/06/02', 500000, 'Owned', 'Kiều Khánh Duy vay');"
    "INSERT INTO Expense(Date, Expense, Category, Note) VALUES('2022/06/03', 1700000, 'Owned', 'Kiều Khánh Duy vay');"
    "INSERT INTO Expense(Date, Expense, Category, Note) VALUES('2022/06/05', 60000, 'Self-development', 'Vé bơi');"
    "INSERT INTO Expense(Date, Expense, Category, Note) VALUES('2022/06/05', 40000, 'Food', 'Ăn 1 cái bánh mỳ và 2 cốc nước mía');"
    "INSERT INTO Expense(Date, Expense, Category, Note) VALUES('2022/06/05', 110000, 'Food', 'Mua thùng mỳ tôm');"
    "INSERT INTO Expense(Date, Expense, Category, Note) VALUES('2022/06/05', 30000, 'Owned', 'Nhật Minh nợ');";

  const char *income_statement =
    "INSERT INTO Income(Date, Income, Category, Note) VALUES('2022/05/31', 500000, 'Food', 'Trả tiền cọc ăn lẩu');"
    "INSERT INTO Income(Date, Income, Category, Note) VALUES('2022/06/03', 150000, 'Education', 'Làm thuê TTCS');";

  const char *exercise_statement =
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/05/22', 'Tập với app Home Workout', 'Indoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/05/23', 'Tập với app Home Workout', 'Indoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/05/24', 'Đạp xe quanh Hồ Tây', 'Outdoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/05/25', 'Đạp xe quanh Hồ Tây', 'Outdoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/05/26', 'Tập với app Home Workout', 'Indoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/05/27', 'Đạp xe quanh Hồ Tây', 'Outdoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/05/30', 'Đạp xe quanh Hồ Tây', 'Outdoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/06/01', 'Đạp xe quanh Hồ Tây', 'Outdoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/06/02', 'Đạp xe quanh Hồ Tây', 'Outdoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/06/03', 'Tập với app Home Workout', 'Indoor');"
    "INSERT INTO Exercise(Date, Activity, Category) VALUES('2022/06/04', 'Đạp xe quanh Hồ Tây', 'Outdoor');"
    "INSERT INTO Exercise(Date, Activity, Category, Note) VALUES('2022/06/05', 'Đi bơi', 'Outdoor', 'Đi bơi ở bể Khăn Quàng Đỏ');";

  const char *retrieve_statement =
    "SELECT * FROM Expense;"
    "SELECT * FROM Income;"
    "SELECT * FROM Exercise;";

  open_database(database_file, &database);

  reset_database(database);

  add_records_to_database(expense_statement, database);
  add_records_to_database(income_statement, database);
  add_records_to_database(exercise_statement, database);

  retrieve_data_from_database(retrieve_statement, database);

  sqlite3_close(database);
  sqlite3_close(database);
  return 0;
}
