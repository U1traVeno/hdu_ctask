//
// Created by U1traVeno on 24-12-18.
//

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <sqlite3.h>

typedef struct {
    int id;
    char* name;
    char* gender;
    char* birthday;
    char* address;
} Employee;

#endif //EMPLOYEE_H
