#include <stdio.h>
#include <stdlib.h>

#include "dal/db.h"
#include "dal/query/employee.h"


int main() {
    int choice;
    sqlite3* db = db_open("sales.db");
    if (db == nullptr) {
        fprintf(stderr, "Cannot open database\n");
        return 1;
    }
    while (1) {
        printf("欢迎进入销售信息管理系统\n");
        printf("1. 录入销售人员信息\n");
        printf("2. 录入产品信息\n");
        printf("3. 录入销售记录\n");
        printf("4. 查询销售记录\n");
        printf("5. 生成销售报表\n");
        printf("0. 退出\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("录入销售人员信息\n");
            break;
        case 2:
            break;
        case 0:
            printf("退出系统\n");
            return 0;
        default:
            printf("无效选择，请重新输入\n");
        }
    }
}
