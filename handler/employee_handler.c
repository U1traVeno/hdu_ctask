//
// Created by U1traVeno on 24-12-18.
//

#include "employee_handler.h"

#include <stdlib.h>

#include "../dal/model/employee.h"
#include "../dal/query/employee_query.h"
#include <string.h>
#include <stdio.h>

// 创建employee结构体，传入id, name, gender, birthday，返回0表示成功，-1表示失败
int add_employee_handler(int id, const char* name, const char* gender, const char* birthday) {
    if (id <= 0 || name == NULL || gender == NULL || birthday == NULL) {
        return -1;
    }

    Employee* new_employee = (Employee*)malloc(sizeof(Employee));
    if (!new_employee) {
        return -1;
    }

    new_employee->base_model.id = id;
    strncpy(new_employee->name, name, sizeof(new_employee->name) - 1);
    new_employee->name[sizeof(new_employee->name) - 1] = '\0';
    strncpy(new_employee->gender, gender, sizeof(new_employee->gender) - 1);
    new_employee->gender[sizeof(new_employee->gender) - 1] = '\0';
    strncpy(new_employee->birthday, birthday, sizeof(new_employee->birthday) - 1);
    new_employee->birthday[sizeof(new_employee->birthday) - 1] = '\0';

    int result = add_employee(new_employee);
    free(new_employee);

    return result == 0 ? 0 : -1; // 如果add_employee返回0则返回0，否则返回-1
}

// 根据id删除员工，返回0表示成功，-1表示失败
int delete_employee_handler(int id) {
    if (id <= 0) {
        return -1;
    }

    int result = delete_employee(id);
    return result == 0 ? 0 : -1;
}

// 更新员工信息，传入与add_employee_handler相同的参数，返回0表示成功，-1表示失败
int update_employee_handler(const int id, const char* name, const char* gender, const char* birthday) {
    if (id <= 0 || name == NULL || gender == NULL || birthday == NULL) {
        return -1;
    }

    Employee* existing_employee = find_employee_by_id_handler(id);
    if (!existing_employee) {
        return -1;
    }

    strncpy(existing_employee->name, name, sizeof(existing_employee->name) - 1);
    existing_employee->name[sizeof(existing_employee->name) - 1] = '\0';
    strncpy(existing_employee->gender, gender, sizeof(existing_employee->gender) - 1);
    existing_employee->gender[sizeof(existing_employee->gender) - 1] = '\0';
    strncpy(existing_employee->birthday, birthday, sizeof(existing_employee->birthday) - 1);
    existing_employee->birthday[sizeof(existing_employee->birthday) - 1] = '\0';

    int result = update_employee(existing_employee);
    return result == 0 ? 0 : -1;
}

// 根据id查找员工，返回员工指针，如果没有找到则返回nullptr
Employee* find_employee_by_id_handler(int id) {
    if (id <= 0) {
        return nullptr;
    }

    Employee* employee = employee_find_by_id(id);
    return employee;
}

// 根据name查找员工，返回员工指针，如果没有找到则返回NULL
Employee* find_employee_by_name_handler(const char* name) {
    if (name == NULL) {
        return nullptr;
    }

    Employee* employee = employee_find_by_name(name);
    return employee;
}

// 查找所有员工，返回员工指针数组，如果没有找到则返回NULL
Employee** find_all_employee_handler() {
    Employee** employees = employee_find_all();
    return employees;
}

