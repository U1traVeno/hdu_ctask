//
// Created by U1traVeno on 24-12-18.
//

#ifndef SALE_H
#define SALE_H
#include "base_model.h"

typedef struct {
    BaseModel base_model;
    int employee_id;
    int product_id;
    int quantity;
    double price;
    char* date;
} Sale;

#endif //SALE_H
