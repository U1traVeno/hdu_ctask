//
// Created by U1traVeno on 24-12-18.
//

#ifndef EMPLOYEE_HANDLER_H
#define EMPLOYEE_HANDLER_H

#include "../dal/model/employee.h"
#include "../dal/query/employee_query.h"

// 创建employee结构体, 传入id, name, gender, birthday, 返回0表示成功, -1表示失败
int add_employee_handler(int id, const char* name, const char* gender, const char* birthday);
// 根据id删除员工, 返回0表示成功, -1表示失败
int delete_employee_handler(int id);
// 更新员工信息, 传入与create_employee相同的参数, 返回0表示成功, -1表示失败(员工不存在)
int update_employee_handler(int id, const char* name, const char* gender, const char* birthday);
// 根据id查找员工, 返回员工指针, 如果没有找到则返回NULL
Employee* find_employee_by_id_handler(int id);
// 根据name查找员工, 返回员工指针, 如果没有找到则返回NULL
Employee* find_employee_by_name_handler(const char* name);
// 查找所有员工, 返回员工指针数组, 如果没有找到则返回NULL
Employee** find_all_employee_handler();

#endif //EMPLOYEE_HANDLER_H
