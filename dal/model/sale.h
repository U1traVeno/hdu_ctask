//
// Created by U1traVeno on 24-12-18.
//

#ifndef SALE_H
#define SALE_H

typedef struct {
    int id;
    int employee_id;
    int product_id;
    int quantity;
    double price;
    char* date;
} Sale;
#endif //SALE_H
