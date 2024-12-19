#include <stdio.h>

#include "dal/db.h"
#include "cli/menu.h"


int main()
{
    sqlite3* db = db_open("sales.db");
    if (db == nullptr) {
        fprintf(stderr, "Cannot open database\n");
        return 1;
    }
    show_main_menu();
    return 0;
}
