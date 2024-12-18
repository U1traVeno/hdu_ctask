//
// Created by U1traVeno on 24-12-17.
//

#include "db.h"
#include <sqlite3.h>

static sqlite3* global_db = nullptr;  // 全局数据库连接

sqlite3* db_open(const char* path) {
    if (global_db != nullptr) {
        return global_db;  // 如果已经打开，直接返回
    }

    int result = sqlite3_open(path, &global_db);
    if (result != SQLITE_OK) {
        return nullptr;
    }

    return global_db;
}

sqlite3* get_db() {
    return global_db;  // 返回全局数据库连接
}

void db_close() {
    if (global_db != nullptr) {
        sqlite3_close(global_db);
        global_db = nullptr;  // 关闭数据库后将指针置为nullptr
    }
}

int execute_sql(const char* sql) {
    if (global_db == nullptr) {
        return -1;  // 没有打开数据库，返回错误
    }

    char* error_message = nullptr;
    int result = sqlite3_exec(global_db, sql, nullptr, nullptr, &error_message);
    if (result != SQLITE_OK) {
        sqlite3_free(error_message);
        return -1;  // 执行失败
    }

    return 0;  // 成功
}



