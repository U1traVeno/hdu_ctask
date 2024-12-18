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

int execute_sql(sqlite3* db, const char* sql) {
    char* errMsg;
    const int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    return 0;
}

void db_close(sqlite3* db) {
    sqlite3_close(db);
}
