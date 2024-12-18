//
// Created by U1traVeno on 24-12-18.
//

#ifndef PRODUCT_H
#define PRODUCT_H
#include "base_model.h"

typedef struct {
    BaseModel base_model;
    char* name;
    char* type;
    char* description;
    double price;
} Product;

#endif //PRODUCT_H
