//
// Created by U1traVeno on 24-12-18.
//

#include "menu.h"
#include <stdio.h>
#include "cil_utils.h"
#include "../handler/employee_handler.h"

const char *main_menu_options[] = {
    "员工信息管理",
    "商品信息管理",
    "销售记录管理",
    "报表查询",
    nullptr
};

const char *employee_menu_options[] = {
    "添加员工",
    "删除员工",
    "修改员工",
    "查询员工",
    "返回",
    nullptr
};

const char *find_employee_menu_options[] = {
    "按编号查询",
    "按姓名查询",
    "返回",
    nullptr
};

const char *product_menu_options[] = {
    "添加商品",
    "删除商品",
    "修改商品",
    "查询商品",
    "返回",
    nullptr
};

const char *find_product_menu_options[] = {
    "按编号查询",
    "按名称查询",
    "返回",
    nullptr
};

const char *sale_menu_options[] = {
    "添加销售记录",
    "删除销售记录",
    "修改销售记录",
    "查询销售记录",
    "返回",
    nullptr
};

const char *find_sale_menu_options[] = {
    "按员工查询",
    "按日期查询",
    "按商品查询",
    "返回",
    nullptr
};
const char *report_menu_options[] = {
    "员工销售报表",
    "商品销售报表",
    "返回",
    nullptr
};

const char *report_employee_menu_options[] = {
    "按员工查询",
    "按日期查询",
    "返回",
    nullptr
};

const char *report_product_menu_options[] = {
    "按商品查询",
    "按日期查询",
    "返回",
    nullptr
};


void show_main_menu() {
    while (1) {
        switch (show_menu("主菜单", main_menu_options)) {
            case 1:
                show_employee_menu();
                break;
            case 2:
                show_product_menu();
                break;
            case 3:
                show_sale_menu();
                break;
            case 4:
                show_report_menu();
                break;
            case 0:
                return;
        }
    }
}

void show_employee_menu() {
    while (1) {
        switch (show_menu("员工信息管理", employee_menu_options)) {
            case 1:
                // add_employee();
                char name[100];
                char gender[10];
                char birthday[20];

                printf("请输入员工姓名: ");
                fgets(name, sizeof(name), stdin);
                printf("请输入员工性别: ");
                fgets(gender, sizeof(gender), stdin);
                printf("请输入员工生日: ");
                fgets(birthday, sizeof(birthday), stdin);
                add_employee_handler(name, gender, birthday);

                break;
            case 2:
                // delete_employee();
                printf("请输入员工编号: ");
                int id = fgetc(stdin);
                delete_employee_handler(id);
                break;
            case 3:
                // update_employee();
                printf("待实现\n");
                break;
            case 4:
                show_find_employee_menu();
                break;
            case 0:
                return;
        }
    }
}

void show_find_employee_menu() {
    while (1) {
        switch (show_menu("查询员工", find_employee_menu_options)) {
            case 1:
                // 获取输入, 调用find_employee_by_id_handler(), 解析Employee结构体, 调用print_employee()
                printf("请输入员工编号: ");
                int id = fgetc(stdin);
                print_employee(find_employee_by_id_handler(id));
                break;
            case 2:
                printf("待实现\n");
                break;
            case 0:
                return;
        }
    }
}

void show_product_menu() {
    while (1) {
        switch (show_menu("商品信息管理", product_menu_options)) {
            case 1:
                // add_product();
                break;
            case 2:
                // delete_product();
                break;
            case 3:
                // update_product();
                break;
            case 4:
                show_find_product_menu();
                break;
            case 0:
                return;
        }
    }
}

void show_find_product_menu() {
    while (1) {
        switch (show_menu("查询商品", find_product_menu_options)) {
            case 1:
                // find_product_by_id();
                break;
            case 2:
                // find_product_by_name();
                break;
            case 0:
                return;
        }
    }
}

void show_sale_menu() {
    while (1) {
        switch (show_menu("销售记录管理", sale_menu_options)) {
            case 1:
                // add_sale();
                break;
            case 2:
                // delete_sale();
                break;
            case 3:
                // update_sale();
                break;
            case 4:
                show_find_sale_menu();
                break;
            case 0:
                return;
        }
    }
}

void show_find_sale_menu() {
    while (1) {
        switch (show_menu("查询销售记录", find_sale_menu_options)) {
            case 1:
                // find_sale_by_id();
                break;
            case 2:
                // find_sale_by_date();
                break;
            case 0:
                return;
        }
    }
}


void show_report_menu() {
    while (1) {
        switch (show_menu("报表查询", report_menu_options)) {
            case 1:
                show_report_employee_menu();
                break;
            case 2:
                show_report_product_menu();
                break;
            case 0:
                return;
        }
    }
}

void show_report_employee_menu() {
    while (1) {
        switch (show_menu("员工销售报表", report_employee_menu_options)) {
            case 1:
                // print_employee_sales_by_date();
                break;
            case 2:
                // print_employee_sales_by_id();
                break;
            case 0:
                return;
        }
    }
}

void show_report_product_menu() {
    while (1) {
        switch (show_menu("商品销售报表", report_product_menu_options)) {
            case 1:
                // print_product_sales_by_date();
                break;
            case 0:
                return;
        }
    }
}

