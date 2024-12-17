//
// Created by U1traVeno on 24-12-17.
//

#include "db.h"
#include <stdio.h>
#include <sqlite3.h>

sqlite3* db_open(const char* path) {
    sqlite3* db;
    const int rc = sqlite3_open(path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }
    return db;
}

void db_close(sqlite3* db) {
    sqlite3_close(db);
}
