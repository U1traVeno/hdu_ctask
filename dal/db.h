//
// Created by U1traVeno on 24-12-17.
//

#ifndef DB_H
#define DB_H

#include <sqlite3.h>

sqlite3* db_open(const char* path);
void db_close(sqlite3* db);

#endif //DB_H
