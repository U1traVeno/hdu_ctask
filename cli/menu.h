//
// Created by U1traVeno on 24-12-18.
//

#ifndef MENU_H
#define MENU_H

void show_main_menu();

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

#endif //MENU_H
