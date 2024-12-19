//
// Created by U1traVeno on 24-12-18.
//

#ifndef REPORT_HANDLER_H
#define REPORT_HANDLER_H
#include "../dal/model/sale.h"
#include "../dal/model/product.h"
#include "../dal/model/employee.h"

void print_sales(Sale** sales);
// 根据日期打印销售产品销售信息
void print_product_sales_by_date(const char* month);
// 根据日期打印员工销售情况
void print_employee_sales_by_date(const char* month);
// 根据员工ID打印销售信息, 按月份分组
void print_employee_sales_by_id(int employee_id);

#endif //REPORT_HANDLER_H
