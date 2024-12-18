//
// Created by U1traVeno on 24-12-18.
//

#ifndef SALES_QUERY_H
#define SALES_QUERY_H
#include "../db.h"
#include "../model/sale.h"

// 创建销售表，如果表不存在则创建，存在则不做任何操作，默认销售表有id, employee_id, product_id, quantity, price, date字段
int create_sales_table(sqlite3* db);
// 增删改查
int add_sales(sqlite3* db, Sale* sale);
int delete_sales(sqlite3* db, int id);
int update_sales(sqlite3* db, Sale* sale);
Sale* sales_find_by_id(sqlite3* db, int id);
Sale* sales_find_by_name(sqlite3* db, char* name);
Sale** sales_find_all(sqlite3* db);
int sales_count(sqlite3* db);

#endif //SALES_QUERY_H
