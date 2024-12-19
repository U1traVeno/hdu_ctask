//
// Created by U1traVeno on 24-12-18.
//

#include "sale_handler.h"

#include <stdlib.h>
#include <string.h>

#include "../dal/query/sale_query.h"

int add_sale_handler(int id, int employee_id, int product_id, int quantity, double price, const char* date) {
    if (id <= 0 || employee_id <= 0 || product_id <= 0 || quantity <= 0 || price <= 0 || date == NULL) {
        return -1;
    }

    Sale* new_sale = (Sale*)malloc(sizeof(Sale));
    if (!new_sale) {
        return -1;
    }

    new_sale->base_model.id = id;
    new_sale->employee_id = employee_id;
    new_sale->product_id = product_id;
    new_sale->quantity = quantity;
    new_sale->price = price;
    new_sale->date = (char*)malloc(strlen(date) + 1);
    if (!new_sale->date) {
        free(new_sale);
        return -1;
    }
    strcpy(new_sale->date, date);

    int result = add_sale(new_sale);
    free(new_sale->date);
    free(new_sale);

    return result == 0 ? 0 : -1;
}

int delete_sale_handler(int id) {
    if (id <= 0) {
        return -1;
    }

    int result = delete_sale(id);
    return result == 0 ? 0 : -1;
}

int update_sale_handler(int id, int employee_id, int product_id, int quantity, double price, const char* date) {
    if (id <= 0 || employee_id <= 0 || product_id <= 0 || quantity <= 0 || price <= 0 || date == NULL) {
        return -1;
    }

    Sale* existing_sale = find_sale_by_id_handler(id);
    if (!existing_sale) {
        return -1;
    }

    existing_sale->employee_id = employee_id;
    existing_sale->product_id = product_id;
    existing_sale->quantity = quantity;
    existing_sale->price = price;
    free(existing_sale->date);
    existing_sale->date = (char*)malloc(strlen(date) + 1);
    if (!existing_sale->date) {
        return -1;
    }
    strcpy(existing_sale->date, date);

    int result = update_sale(existing_sale);
    free(existing_sale->date);

    return result == 0 ? 0 : -1;
}

Sale* find_sale_by_id_handler(int id) {
    if (id <= 0) {
        return nullptr;
    }

    return sale_find_by_id(id);
}

Sale** find_sale_by_employee_id_handler(int employee_id) {
    if (employee_id <= 0) {
        return nullptr;
    }

    return sale_find_by_employee_id(employee_id);
}

Sale** find_sale_by_product_id_handler(int product_id) {
    if (product_id <= 0) {
        return nullptr;
    }

    return sale_find_by_product_id(product_id);
}

Sale** find_all_sale_handler() {
    return sale_find_all();
}

