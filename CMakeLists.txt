cmake_minimum_required(VERSION 3.30)
project(hdu_ctask C)

set(CMAKE_C_STANDARD 23)

FIND_PACKAGE(SQLite3 REQUIRED)

add_executable(hdu_ctask main.c
        dal/db.c
        dal/db.h
        dal/query/employee_query.c
        dal/query/employee_query.h
        dal/query/product_query.c
        dal/query/product_query.h
        dal/query/sale_query.c
        dal/query/sale_query.h
        dal/model/employee.h
        dal/model/product.h
        dal/model/sale.h
        dal/model/base_model.h
        util/utils.c
        util/utils.h
        handler/report_handler.c
        handler/report_handler.h
        handler/employee_handler.c
        handler/employee_handler.h
        handler/product_handler.c
        handler/product_handler.h
        handler/sale_handler.c
        handler/sale_handler.h
        cli/menu.c
        cli/menu.h
        cli/cil_utils.c
        cli/cil_utils.h
)

if(SQLITE3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
    target_link_libraries(hdu_ctask ${SQLite3_LIBRARIES})
else()
    message(FATAL_ERROR "SQLite3 not found")
endif()


