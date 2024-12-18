//
// Created by U1traVeno on 24-12-17.
//

#include "employee_query.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 创建员工表
int create_employee_table(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS employees ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name TEXT NOT NULL,"
                      "gender TEXT,"
                      "birthday TEXT,"
                      "created_at TEXT DEFAULT CURRENT_TIMESTAMP,"
                      "updated_at TEXT DEFAULT CURRENT_TIMESTAMP,"
                      "deleted_at TEXT"
                      ");";
    return execute_sql(db, sql);
}

// 增加员工
int add_employee(sqlite3* db, const Employee* employee) {
    const char* sql = "INSERT INTO employees (name, gender, birthday) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    sqlite3_bind_text(stmt, 1, employee->name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, employee->gender, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, employee->birthday, -1, SQLITE_TRANSIENT);

    const int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert employee: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

// 删除员工
int delete_employee(sqlite3* db, int id) {
    const char* sql = "DELETE FROM employees WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    sqlite3_bind_int(stmt, 1, id);

    const int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to delete employee: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

// 更新员工
int update_employee(sqlite3* db, const Employee* employee) {
    const char* sql = "UPDATE employees SET name = ?, gender = ?, birthday = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    sqlite3_bind_text(stmt, 1, employee->name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, employee->gender, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, employee->birthday, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, employee->base_model.id);

    const int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to update employee: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

// 按ID查找员工
Employee* employee_find_by_id(sqlite3* db, int id) {
    const char* sql = "SELECT id, name, gender, birthday, created_at, updated_at, deleted_at FROM employees WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, id);

    Employee* employee = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        employee = malloc(sizeof(Employee)); // 此处需要用malloc分配内存, 因为在函数结束后需要返回一个指针
        employee->base_model.id = sqlite3_column_int(stmt, 0);
        employee->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        employee->gender = strdup((const char*)sqlite3_column_text(stmt, 2));
        employee->birthday = strdup((const char*)sqlite3_column_text(stmt, 3));
        employee->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 4));
        employee->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        employee->base_model.deleted_at = sqlite3_column_text(stmt, 6) ? strdup((const char*)sqlite3_column_text(stmt, 6)) : nullptr;
    }

    sqlite3_finalize(stmt);
    return employee;
}

// 按名字查找员工
Employee* employee_find_by_name(sqlite3* db, const char* name) {
    const char* sql = "SELECT id, name, gender, birthday, created_at, updated_at, deleted_at FROM employees WHERE name = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);

    Employee* employee = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        employee = malloc(sizeof(Employee));
        employee->base_model.id = sqlite3_column_int(stmt, 0);
        employee->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        employee->gender = strdup((const char*)sqlite3_column_text(stmt, 2));
        employee->birthday = strdup((const char*)sqlite3_column_text(stmt, 3));
        employee->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 4));
        employee->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        employee->base_model.deleted_at = sqlite3_column_text(stmt, 6) ? strdup((const char*)sqlite3_column_text(stmt, 6)) : nullptr;
    }

    sqlite3_finalize(stmt);
    return employee;
}

void free_employees(Employee** employees) {
    for (int i = 0; employees[i] != nullptr; i++) {
        free(employees[i]->base_model.created_at);
        free(employees[i]->base_model.updated_at);
        free(employees[i]->base_model.deleted_at);
        free(employees[i]);
    }
    free(employees);
}
// 查找所有员工
Employee** employee_find_all(sqlite3* db) {
    const char* sql = "SELECT id, name, gender, birthday, created_at, updated_at, deleted_at FROM employees;";
    sqlite3_stmt* stmt;
    // 准备SQL语句
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    Employee** employees = nullptr;
    int count = 0;
    // 遍历结果集
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        void * tmp = realloc(employees, sizeof(Employee*) * (count + 1));
        if (tmp == nullptr) {
            // 释放内存
            fprintf(stderr, "Failed to allocate memory\n");
            free_employees(employees);
            sqlite3_finalize(stmt);
            return nullptr;
        }
        // 更新employees指针
        employees = tmp;
        // 分配内存
        Employee* employee = malloc(sizeof(Employee));

        // 从结果集中读取数据
        employee->base_model.id = sqlite3_column_int(stmt, 0);
        employee->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        employee->gender = strdup((const char*)sqlite3_column_text(stmt, 2));
        employee->birthday = strdup((const char*)sqlite3_column_text(stmt, 3));
        employee->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 4));
        employee->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        employee->base_model.deleted_at = sqlite3_column_text(stmt, 6) ? strdup((const char*)sqlite3_column_text(stmt, 6)) : nullptr;
        // 更新数组
        employees[count] = employee;
        free_employees(tmp);
    }

    // 防止realloc失败导致空指针
    void * tmp = realloc(employees, sizeof(Employee*) * (count + 1));
    if (tmp == nullptr) {
        fprintf(stderr, "Failed to allocate memory for final null-terminated array\n");
        free_employees(employees);
        sqlite3_finalize(stmt);
        return nullptr;
    }
    employees = tmp;

    employees[count] = nullptr; // 在数组的最后一个元素设置为nullptr，以便在遍历时判断数组的结束

    sqlite3_finalize(stmt);
    return employees;
}


// 员工总数
int employee_count(sqlite3* db) {
    const char* sql = "SELECT COUNT(*) FROM employees;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return count;
}