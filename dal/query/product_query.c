//
// Created by U1traVeno on 24-12-17.
//

#include "product_query.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_product_table(sqlite3* db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS products ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name TEXT NOT NULL,"
                      "type TEXT,"
                      "description TEXT,"
                      "price REAL NOT NULL,"
                      "created_at TEXT DEFAULT CURRENT_TIMESTAMP,"
                      "updated_at TEXT DEFAULT CURRENT_TIMESTAMP,"
                      "deleted_at TEXT"
                      ");";
    return execute_sql(db, sql);
}

int add_product(sqlite3* db, Product* product) {
    const char* sql = "INSERT INTO products (name, type, description, price) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    sqlite3_bind_text(stmt, 1, product->name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, product->description, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, product->type, -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, product->price);

    const int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert product: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

int delete_product(sqlite3* db, int id) {
    const char* sql = "DELETE FROM products WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    sqlite3_bind_int(stmt, 1, id);

    const int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to delete product: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

Product* product_find_by_id(sqlite3* db, int id) {
    const char* sql = "SELECT id, name, type, description, price, created_at, updated_at, deleted_at FROM products WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, id);

    Product* product = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        product = malloc(sizeof(Product));
        product->base_model.id = sqlite3_column_int(stmt, 0);
        product->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        product->type = strdup((const char*)sqlite3_column_text(stmt, 2));
        product->description = strdup((const char*)sqlite3_column_text(stmt, 3));
        product->price = sqlite3_column_double(stmt, 4);
        product->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        product->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 6));
        product->base_model.deleted_at = sqlite3_column_text(stmt, 7) ? strdup((const char*)sqlite3_column_text(stmt, 7)) : nullptr;
    }

    sqlite3_finalize(stmt);
    return product;
}
// 按名字查找产品
Product* product_find_by_name(sqlite3* db, const char* name) {
    const char* sql = "SELECT id, name, type, description, price, created_at, updated_at, deleted_at FROM products WHERE name = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);

    Product* product = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        product = malloc(sizeof(Product));
        product->base_model.id = sqlite3_column_int(stmt, 0);
        product->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        product->type = strdup((const char*)sqlite3_column_text(stmt, 2));
        product->description = strdup((const char*)sqlite3_column_text(stmt, 3));
        product->price = sqlite3_column_double(stmt, 4);
        product->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        product->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 6));
        product->base_model.deleted_at = sqlite3_column_text(stmt, 7) ? strdup((const char*)sqlite3_column_text(stmt, 7)) : NULL;
    }

    sqlite3_finalize(stmt);
    return product;
}

// 查找所有产品
// TODO 这里的实现有内存泄漏，需要释放内存
Product** product_find_all(sqlite3* db) {
    const char* sql = "SELECT id, name, type, description, price, created_at, updated_at, deleted_at FROM products;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }

    Product** products = nullptr;
    int count = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        products = realloc(products, sizeof(Product*) * (count + 1));
        if (!products) {
            fprintf(stderr, "Failed to allocate memory\n");
            return nullptr; // 此处使用malloc分配内存
        }
        Product* product = malloc(sizeof(Product));

        product->base_model.id = sqlite3_column_int(stmt, 0);
        product->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        product->type = strdup((const char*)sqlite3_column_text(stmt, 2));
        product->description = strdup((const char*)sqlite3_column_text(stmt, 3));
        product->price = sqlite3_column_double(stmt, 4);
        product->base_model.created_at = strdup((const char*)sqlite3_column_text(stmt, 5));
        product->base_model.updated_at = strdup((const char*)sqlite3_column_text(stmt, 6));
        product->base_model.deleted_at = sqlite3_column_text(stmt, 7) ? strdup((const char*)sqlite3_column_text(stmt, 7)) : nullptr;

        products[count++] = product;
    }

    products = realloc(products, sizeof(Product*) * (count + 1));
    products[count] = nullptr; // Null-terminate the array

    sqlite3_finalize(stmt);
    return products;
}

// 产品总数
int product_count(sqlite3* db) {
    const char* sql = "SELECT COUNT(*) FROM products;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        fprintf(stderr, "Failed to get product count: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}