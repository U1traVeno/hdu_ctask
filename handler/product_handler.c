//
// Created by U1traVeno on 24-12-18.
//

#include "product_handler.h"

#include <stdlib.h>
#include <string.h>

#include "../dal/query/product_query.h"

int add_product_handler(int id, const char* name, const char* type, double price, const char* description) {
    // 创建产品结构体
    if (id <= 0 || name == NULL || type == NULL || price <= 0 || description == NULL) {
        return -1;
    }

    Product* new_product = (Product*)malloc(sizeof(Product));
    if (!new_product) {
        return -1;
    }

    new_product->base_model.id = id;
    strncpy(new_product->name, name, sizeof(new_product->name) - 1);
    new_product->name[sizeof(new_product->name) - 1] = '\0';
    strncpy(new_product->type, type, sizeof(new_product->type) - 1);
    new_product->type[sizeof(new_product->type) - 1] = '\0';
    new_product->price = price; // 因为price是double类型，所以不需要担心越界
    strncpy(new_product->description, description, sizeof(new_product->description) - 1);
    new_product->description[sizeof(new_product->description) - 1] = '\0';

    int result = add_product(new_product);
    free(new_product);

    return result == 0 ? 0 : -1; // 如果add_product返回0则返回0，否则返回-1
}

int delete_product_handler(int id) {
    if (id <= 0) {
        return -1;
    }

    int result = delete_product(id);
    return result == 0 ? 0 : -1;
}

int update_product_handler(int id, const char* name, const char* type, double price, const char* description) {
    if (id <= 0 || name == NULL || type == NULL || price <= 0 || description == NULL) {
        return -1;
    }

    Product* existing_product = find_product_by_id_handler(id);
    if (!existing_product) {
        return -1;
    }

    strncpy(existing_product->name, name, sizeof(existing_product->name) - 1);
    existing_product->name[sizeof(existing_product->name) - 1] = '\0';
    strncpy(existing_product->type, type, sizeof(existing_product->type) - 1);
    existing_product->type[sizeof(existing_product->type) - 1] = '\0';
    existing_product->price = price;
    strncpy(existing_product->description, description, sizeof(existing_product->description) - 1);
    existing_product->description[sizeof(existing_product->description) - 1] = '\0';

    int result = update_product(existing_product);

    return result == 0 ? 0 : -1;
}

Product* find_product_by_id_handler(int id) {
    if (id <= 0) {
        return nullptr;
    }
    return product_find_by_id(id);
}

Product* find_product_by_name_handler(const char* name) {
    if (name == NULL) {
        return nullptr;
    }
    return product_find_by_name(name);
}

Product** find_all_product_handler() {
    if (product_count() == 0) {
        return nullptr;
    }
    return product_find_all();
}


