//
// Created by U1traVeno on 24-12-17.
//

#ifndef PRODUCT_QUERY_H
#define PRODUCT_QUERY_H
#include "../db.h"
#include "../model/product.h"

// 创建产品表，如果表不存在则创建，存在则不做任何操作，默认产品表有id, name, type, description, price字段, 其中id为主键
int create_product_table(sqlite3* db);
// 增删改查
int add_product(sqlite3* db, Product* product);
int delete_product(sqlite3* db, int id);
int update_product(sqlite3* db, Product* product);
Product* product_find_by_id(sqlite3* db, int id);
Product* product_find_by_name(sqlite3* db, const char* name);
Product** product_find_all(sqlite3* db);
int product_count(sqlite3* db);

#endif //PRODUCT_QUERY_H
