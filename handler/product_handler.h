//
// Created by U1traVeno on 24-12-18.
//

#ifndef PRODUCT_HANDLER_H
#define PRODUCT_HANDLER_H

#include "../dal/model/product.h"

// 创建product结构体, 传入id, name, type, price, description 返回0表示成功, -1表示失败
int add_product_handler(int id, const char* name, const char* type, double price, const char* description);
// 根据id删除产品, 返回0表示成功, -1表示失败
int delete_product_handler(int id);
// 更新产品信息, 传入与add_product_handler相同的参数, 返回0表示成功, -1表示失败
int update_product_handler(int id, const char* name, const char* type, double price, const char* description);
// 根据id查找产品, 返回产品指针, 如果没有找到则返回nullptr
Product* find_product_by_id_handler(int id);
// 根据name查找产品, 返回产品指针, 如果没有找到则返回nullptr
Product* find_product_by_name_handler(const char* name);
// 查找所有产品, 返回产品指针数组, 如果没有找到则返回nullptr
Product** find_all_product_handler();

#endif //PRODUCT_HANDLER_H
