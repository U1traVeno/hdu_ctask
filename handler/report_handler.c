//
// Created by U1traVeno on 24-12-18.
//

#include "report_handler.h"

#include <stdio.h>

#include "../dal/query/sale_query.h"

void print_sales(Sale** sales) {
    if (sales == nullptr) {
        printf("No sales found\n");
        return;
    }
    for (int i = 0; sales[i] != nullptr; i++) {
        printf("ID: %d\n", sales[i]->base_model.id);
        printf("Employee ID: %d\n", sales[i]->employee_id);
        printf("Product ID: %d\n", sales[i]->product_id);
        printf("Quantity: %d\n", sales[i]->quantity);
        printf("Price: %.2f\n", sales[i]->price);
        printf("Date: %s\n", sales[i]->date);
        printf("Created At: %s\n", sales[i]->base_model.created_at);
        printf("Updated At: %s\n", sales[i]->base_model.updated_at);
        printf("Deleted At: %s\n", sales[i]->base_model.deleted_at);
        printf("\n");
    }
}

void print_product_sales_by_date(const char* month) {
    Sale** sales = sale_find_by_date(month);
    print_sales(sales);
}

void print_employee_sales_by_date(const char* month) {
    Sale** sales = sale_find_by_date(month);
    print_sales(sales);
}

void print_employee_sales_by_id(int employee_id) {
    Sale** sales = sale_find_by_employee_id(employee_id);
    print_sales(sales);
}
