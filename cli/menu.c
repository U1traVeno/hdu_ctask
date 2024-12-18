//
// Created by U1traVeno on 24-12-18.
//

#include "menu.h"
#include <stdio.h>
#include "cil_utils.h"

void show_main_menu() {
    while (1) {
        switch (show_menu("主菜单", main_menu_options)) {
            case 1:
                printf("添加学生\n");
                break;
            case 2:
                printf("删除学生\n");
                break;
            case 3:
                printf("显示学生\n");
                break;
            case 0:
                printf("退出\n");
                return;
            default:
                printf("未知选项\n");
                break;
        }
    }
}
