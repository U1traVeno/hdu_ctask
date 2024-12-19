//
// Created by U1traVeno on 24-12-18.
//

#include "report_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../dal/query/sale_query.h"
#include "../dal/query/product_query.h"
#include "../dal/query/employee_query.h"
#include "../util/utils.h"

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

// 用于qsort的比较函数
int compare_sales_amount(const void* a, const void* b) {
    const Sale *sale_a = a;
    const Sale *sale_b = b;

    double amount_a = sale_a->price * sale_a->quantity;
    double amount_b = sale_b->price * sale_b->quantity;

    if (amount_a < amount_b) {
        return -1;
    }
    if (amount_a > amount_b) {
        return 1;
    }
    return 0;
}

void print_product_sales_by_date(const char* month)
{
    Sale** sales = sale_find_by_date(month);
    // 计算记录总数
    int sale_count = 0;
    for (int i = 0; sales[i] != nullptr; i++) {
        sale_count++;
    }
    // 若无记录则输出提示信息
    if (sales == nullptr || sale_count == 0) {
        printf("No sales found\n");
        return;
    }

    Product** products = product_find_all();

    // 汇总销售信息
    struct {
        int product_id;
        int total_quantity;
        double total_sales_amount;
    } product_sales[sale_count];

    memset(product_sales, 0, sizeof(product_sales)); // 初始化销售信息

    // 遍历销售记录，计算销售额
    for (int i = 0; i < sale_count; ++i) {
        int product_id = sales[i]->product_id;
        double amount = sales[i]->price * sales[i]->quantity; // 销售额

        product_sales[product_id].product_id = product_id;
        product_sales[product_id].total_quantity += sales[i]->quantity;
        product_sales[product_id].total_sales_amount += amount;
    }
    // 排序
    qsort(product_sales, sales_count, sizeof(product_sales[0]), compare_sales_amount);

    // 打印表格
    printf("\n 产品销售情况报表 \n");
    printf("%-10s %-20s %-15s %-15s\n", "产品ID", "产品名称", "销售数量", "销售额");
    for (int i = 0; i < sale_count; ++i) {
        if (product_sales[i].product_id == 0) {
            continue;
        }
        Product* product = product_find_by_id(product_sales[i].product_id);
        printf("%-10d %-20s %-15d %-15.2f\n",
            product_sales[i].product_id,
            product->name,
            product_sales[i].total_quantity,
            product_sales[i].total_sales_amount);
    }
}

void print_employee_sales_by_date(const char* month) {
    Sale** sales = sale_find_by_date(month);
    // 计算记录总数
    int sale_count = 0;
    for (int i = 0; sales[i] != nullptr; i++) {
        sale_count++;
    }
    // 若无记录则输出提示信息
    if (sales == nullptr || sale_count == 0) {
        printf("No sales found\n");
        return;
    }

    // 汇总销售信息
    struct {
        int employee_id;
        int total_quantity;
        double total_sales_amount;
    } employee_sales[sale_count];

    memset(employee_sales, 0, sizeof(employee_sales)); // 初始化销售信息

    // 遍历销售记录，计算销售额
    for (int i = 0; i < sale_count; ++i) {
        int employee_id = sales[i]->employee_id;
        double amount = sales[i]->price * sales[i]->quantity; // 销售额

        employee_sales[employee_id].employee_id = employee_id;
        employee_sales[employee_id].total_quantity += sales[i]->quantity;
        employee_sales[employee_id].total_sales_amount += amount;
    }
    // 排序
    qsort(employee_sales, sales_count, sizeof(employee_sales[0]), compare_sales_amount);

    // 打印表格
    printf("\n 员工销售情况报表 \n");
    printf("%-10s %-20s %-15s %-15s\n", "员工ID", "员工姓名", "销售数量", "销售额");
    for (int i = 0; i < sale_count; ++i) {
        if (employee_sales[i].employee_id == 0) {
            continue;
        }
        Employee* employee = employee_find_by_id(employee_sales[i].employee_id);
        printf("%-10d %-20s %-15d %-15.2f\n",
            employee_sales[i].employee_id,
            employee->name,
            employee_sales[i].total_quantity,
            employee_sales[i].total_sales_amount);
    }
}

void print_employee_sales_by_id(int employee_id) {
    Sale** sales = sale_find_by_employee_id(employee_id);
    // 计算记录总数
    int sale_count = 0;
    for (int i = 0; sales[i] != nullptr; i++) {
        sale_count++;
    }
    // 若无记录则输出提示信息
    if (sales == nullptr || sale_count == 0) {
        printf("No sales found\n");
        return;
    }

    // 汇总每月销售额
    struct {
        char* month;
        double monthly_sales_amount;
    } monthly_sales[sale_count];

    memset(monthly_sales, 0, sizeof(monthly_sales)); // 初始化销售信息, 分配内存

    // 计算销售总额
    for (int i = 0; i < sale_count; ++i) {
        char* month = extract_month_from_date(sales[i]->date);
        double amount = sales[i]->price * sales[i]->quantity;

        monthly_sales[i].month = month;
        monthly_sales[i].monthly_sales_amount += amount;
    }
    // 按月份排序
    qsort(monthly_sales, sale_count, sizeof(monthly_sales[0]), compare_sales_amount);

    // 打印表格
    printf("\n 员工销售情况报表 \n");
    printf("%-10s %-20s \n", "月份", "销售额");
    for (int i = 0; i < sale_count; ++i) {
        if (monthly_sales[i].month == nullptr) {
            continue;
        }
        printf("%-10s %-20.2f\n",
            monthly_sales[i].month,
            monthly_sales[i].monthly_sales_amount);
    }
}

