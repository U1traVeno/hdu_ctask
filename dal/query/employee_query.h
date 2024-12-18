//
// Created by U1traVeno on 24-12-17.
//

#ifndef EMPLOYEE_QUERY_H
#define EMPLOYEE_QUERY_H
#include "../db.h"
#include "../model/employee.h"

// 创建员工表，如果表不存在则创建，存在则不做任何操作，默认员工表有id, name, gender, birthday字段, 其中id为主键
int create_employee_table(sqlite3* db);
// 增删改查
int add_employee(sqlite3* db, const Employee* employee);
int delete_employee(sqlite3* db, int id);
int update_employee(sqlite3* db, const Employee* employee);
Employee* employee_find_by_id(sqlite3* db, int id);
Employee* employee_find_by_name(sqlite3* db, const char* name);
Employee** employee_find_all(sqlite3* db);
int employee_count(sqlite3* db);

#endif //EMPLOYEE_QUERY_H
