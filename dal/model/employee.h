//
// Created by U1traVeno on 24-12-18.
//

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "base_model.h"
typedef struct {
    BaseModel base_model;
    char* name;
    char* gender;
    char* birthday;
} Employee;

#endif //EMPLOYEE_H
