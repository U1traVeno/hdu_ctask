//
// Created by U1traVeno on 24-12-18.
//

#ifndef SALE_HANDLER_H
#define SALE_HANDLER_H
#include "../dal/model/sale.h"

// 创建sale结构体, 传入id, employee_id, product_id, quantity, price, date 返回0表示成功, -1表示失败
int add_sale_handler(int id, int employee_id, int product_id, int quantity, double price, const char* date);
// 根据id删除销售记录, 返回0表示成功, -1表示失败
int delete_sale_handler(int id);
// 更新销售记录, 传入与add_sale_handler相同的参数, 返回0表示成功, -1表示失败
int update_sale_handler(int id, int employee_id, int product_id, int quantity, double price, const char* date);
// 根据id查找销售记录, 返回销售记录指针, 如果没有找到则返回nullptr
Sale* find_sale_by_id_handler(int id);
// 根据employee_id查找销售记录, 返回销售记录指针, 如果没有找到则返回nullptr
Sale* find_sale_by_employee_id_handler(int employee_id);
// 根据product_id查找销售记录, 返回销售记录指针, 如果没有找到则返回nullptr
Sale* find_sale_by_product_id_handler(int product_id);
// 查找所有销售记录, 返回销售记录指针数组, 如果没有找到则返回nullptr
Sale** find_all_sale_handler();

#endif //SALE_HANDLER_H
