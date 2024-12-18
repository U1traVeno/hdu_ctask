//
// Created by U1traVeno on 24-12-18.
//

#include "cil_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int show_menu(const char *title, const char *menu_options[]) {
    char *endptr; // strtol() 的第二个参数

    // 自动计算选项数量
    int num_options = 0;
    while (menu_options[num_options] != NULL) {
        num_options++;
    }

    while (1) {
        char input[100];
        // 显示菜单
        printf("\n--- %s ---\n", title); //显示菜单标题
        for (int i = 0; i < num_options; ++i) {
            printf("%d. %s\n", i + 1, menu_options[i]);
        }
        printf("0. 退出\n");
        printf("请选择: ");

        // 获取用户输入
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("读取输入失败，请重试。\n");
            continue;
        }

        // 转换输入为整数
        errno = 0;
        int choice = strtol(input, &endptr, 10); // long int, strtol() returns a long int

        // 检查输入是否为空或包含非数字字符
        if (endptr == input || *endptr != '\n') {
            printf("无效输入，请输入一个数字。\n");
            continue;
        }

        // 检查是否超出整数范围
        if (errno == ERANGE || choice < 0 || choice > num_options) {
            printf("选项超出范围，请输入 0 到 %d 之间的数字。\n", num_options);
            continue;
        }

        // 有效选择
        return choice;
    }
}