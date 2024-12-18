//
// Created by U1traVeno on 24-12-17.
//

#ifndef PRODUCT_QUERY_H
#define PRODUCT_QUERY_H
#include "../model/product.h"

// 创建产品表，如果表不存在则创建，存在则不做任何操作，默认产品表有id, name, type, description, price字段, 其中id为主键
int create_product_table();
// 增删改查
int add_product(Product* product);
int delete_product(int id);
int update_product(Product* product);
Product* product_find_by_id(int id);
Product* product_find_by_name(const char* name);
Product** product_find_all();
int product_count();

#endif //PRODUCT_QUERY_H
