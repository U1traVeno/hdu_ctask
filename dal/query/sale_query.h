//
// Created by U1traVeno on 24-12-18.
//

#ifndef SALES_QUERY_H
#define SALES_QUERY_H
#include "../model/sale.h"

// 创建销售表，如果表不存在则创建，存在则不做任何操作，默认销售表有id, employee_id, product_id, quantity, price, date字段
int create_sales_table();
// 增删改查
int add_sales(Sale* sale);
int delete_sales(int id);
int update_sales(Sale* sale);
Sale* sales_find_by_id(int id);
Sale* sales_find_by_employee_id(int employee_id);
Sale* sales_find_by_product_id(int product_id);
Sale** sales_find_all();
int sales_count();

#endif //SALES_QUERY_H
