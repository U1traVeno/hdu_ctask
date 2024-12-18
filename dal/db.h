//
// Created by U1traVeno on 24-12-17.
//

#ifndef DB_H
#define DB_H

#include <sqlite3.h>

// 打开数据库
sqlite3* db_open(const char* path);

// 获取数据库连接
sqlite3* get_db();

// 执行SQL语句
int execute_sql(const char* sql);

// 关闭数据库
void db_close();

#endif //DB_H
