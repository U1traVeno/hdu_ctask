//
// Created by U1traVeno on 24-12-18.
//

#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <time.h>

const char* validate_date_format(const char *date) {
    regex_t regex;
    int reti;

    // 匹配 YYYY-MM-DD 格式
    reti = regcomp(&regex, "^(\\d{4})-(\\d{2})-(\\d{2})$", REG_EXTENDED);
    if (reti == 0 && regexec(&regex, date, 0, NULL, 0) == 0) {
        regfree(&regex);
        return "%Y-%m-%d"; // 完整日期格式 (YYYY-MM-DD)
    }

    // 匹配 YYYY-MM 格式
    reti = regcomp(&regex, "^(\\d{4})-(\\d{2})$", REG_EXTENDED);
    if (reti == 0 && regexec(&regex, date, 0, NULL, 0) == 0) {
        regfree(&regex);
        return "%Y-%m"; // 月份格式 (YYYY-MM)
    }

    // 匹配 YYYY 格式
    reti = regcomp(&regex, "^(\\d{4})$", REG_EXTENDED);
    if (reti == 0 && regexec(&regex, date, 0, NULL, 0) == 0) {
        regfree(&regex);
        return "%Y"; // 年份格式 (YYYY)
    }

    // 如果不符合任何格式
    regfree(&regex);
    return nullptr; // 无效日期格式
}

char* extract_month_from_date(char *date) {
    const char* format = validate_date_format(date);
    char* month = malloc(8);
    if (format == nullptr) {
        return nullptr;
    }
    strncpy(month, date, 7);
    return month;
}
