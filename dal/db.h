//
// Created by U1traVeno on 24-12-17.
//

#ifndef DB_H
#define DB_H

#include <sqlite3.h>

sqlite3* db_open(const char* path);
// 执行sql语句
int execute_sql(sqlite3* db, const char* sql);
void db_close(sqlite3* db);

// 各个表通用字段结构体，包含ID, CreatedAt, UpdatedAt, DeletedAt, 用于嵌入到各个表的结构体中
typedef struct {
    int id;
    char* created_at;
    char* updated_at;
    char* deleted_at;
} BaseModel;
#endif //DB_H
