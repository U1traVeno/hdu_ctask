//
// Created by U1traVeno on 24-12-18.
//

#include "sale_query.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_sale_table(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS sales ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "product_id INTEGER NOT NULL,"
                      "employee_id INTEGER NOT NULL,"
                      "quantity INTEGER NOT NULL,"
                      "price REAL NOT NULL,"
                      "created_at TEXT DEFAULT CURRENT_TIMESTAMP,"
                      "updated_at TEXT DEFAULT CURRENT_TIMESTAMP,"
                      "deleted_at TEXT"
                      ");";
    return execute_sql(db, sql);
}

int add_sale(sqlite3* db, const Sale* sale) {
    const char* sql = "INSERT INTO sales (product_id, employee_id, quantity, price) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    sqlite3_bind_int(stmt, 1, sale->product_id);
    sqlite3_bind_int(stmt, 2, sale->employee_id);
    sqlite3_bind_int(stmt, 3, sale->quantity);
    sqlite3_bind_double(stmt, 4, sale->price);

    const int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert sale: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

int delete_sale(sqlite3* db, const int id) {
    const char* sql = "DELETE FROM sales WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    sqlite3_bind_int(stmt, 1, id);

    const int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to delete sale: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

int update_sale(sqlite3* db, const Sale* sale) {
    const char* sql = "UPDATE sales SET product_id = ?, employee_id = ?, quantity = ?, price = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    sqlite3_bind_int(stmt, 1, sale->product_id);
    sqlite3_bind_int(stmt, 2, sale->employee_id);
    sqlite3_bind_int(stmt, 3, sale->quantity);
    sqlite3_bind_double(stmt, 4, sale->price);
    sqlite3_bind_int(stmt, 5, sale->base_model.id);

    const int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to update sale: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

Sale* sale_find_by_id(sqlite3* db, const int id) {
    const char* sql = "SELECT id, product_id, employee_id, quantity, price, created_at, updated_at, deleted_at FROM sales WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, id);

    Sale* sale = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sale = malloc(sizeof(Sale));
        sale->base_model.id = sqlite3_column_int(stmt, 0);
        sale->product_id = sqlite3_column_int(stmt, 1);
        sale->employee_id = sqlite3_column_int(stmt, 2);
        sale->quantity = sqlite3_column_int(stmt, 3);
        sale->price = sqlite3_column_double(stmt, 4);
        sale->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        sale->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 6));
        sale->base_model.deleted_at = sqlite3_column_text(stmt, 7) ? strdup((const char*)sqlite3_column_text(stmt, 7)) : nullptr;
    }

    sqlite3_finalize(stmt);
    return sale;
}

Sale* sale_find_by_employee_id(sqlite3* db, const int employee_id) {
    const char* sql = "SELECT id, product_id, employee_id, quantity, price, created_at, updated_at, deleted_at FROM sales WHERE employee_id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, employee_id);

    Sale* sale = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sale = malloc(sizeof(Sale));
        sale->base_model.id = sqlite3_column_int(stmt, 0);
        sale->product_id = sqlite3_column_int(stmt, 1);
        sale->employee_id = sqlite3_column_int(stmt, 2);
        sale->quantity = sqlite3_column_int(stmt, 3);
        sale->price = sqlite3_column_double(stmt, 4);
        sale->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        sale->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 6));
        sale->base_model.deleted_at = sqlite3_column_text(stmt, 7) ? strdup((const char*)sqlite3_column_text(stmt, 7)) : nullptr;
    }

    sqlite3_finalize(stmt);
    return sale;
}

Sale* sale_find_by_product_id(sqlite3* db, const int product_id) {
    const char* sql = "SELECT id, product_id, employee_id, quantity, price, created_at, updated_at, deleted_at FROM sales WHERE product_id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, product_id);

    Sale* sale = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sale = malloc(sizeof(Sale));
        sale->base_model.id = sqlite3_column_int(stmt, 0);
        sale->product_id = sqlite3_column_int(stmt, 1);
        sale->employee_id = sqlite3_column_int(stmt, 2);
        sale->quantity = sqlite3_column_int(stmt, 3);
        sale->price = sqlite3_column_double(stmt, 4);
        sale->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        sale->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 6));
        sale->base_model.deleted_at = sqlite3_column_text(stmt, 7) ? strdup((const char*)sqlite3_column_text(stmt, 7)) : nullptr;
    }

    sqlite3_finalize(stmt);
    return sale;
}

// TODO 这里的实现有内存泄漏，需要释放内存
Sale** sale_find_all(sqlite3* db) {
    const char* sql = "SELECT id, product_id, employee_id, quantity, price, created_at, updated_at, deleted_at FROM sales;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    Sale** sales = nullptr;
    int count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        sales = realloc(sales, sizeof(Sale*) * (count + 1));
        sales[count] = malloc(sizeof(Sale));
        sales[count]->base_model.id = sqlite3_column_int(stmt, 0);
        sales[count]->product_id = sqlite3_column_int(stmt, 1);
        sales[count]->employee_id = sqlite3_column_int(stmt, 2);
        sales[count]->quantity = sqlite3_column_int(stmt, 3);
        sales[count]->price = sqlite3_column_double(stmt, 4);
        sales[count]->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        sales[count]->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 6));
        sales[count]->base_model.deleted_at = sqlite3_column_text(stmt, 7) ? strdup((const char*)sqlite3_column_text(stmt, 7)) : nullptr;
        count++;
    }

    sqlite3_finalize(stmt);
    return sales;
}

int sale_count(sqlite3* db) {
    const char* sql = "SELECT COUNT(*) FROM sales;";
    sqlite3_stmt* stmt;
    int count = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return count;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return count;
}