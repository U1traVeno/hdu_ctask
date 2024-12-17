cmake_minimum_required(VERSION 3.30)
project(hdu_ctask C)

set(CMAKE_C_STANDARD 23)

FIND_PACKAGE(SQLite3 REQUIRED)

add_executable(hdu_ctask main.c
        dal/db.c
        dal/db.h
        dal/query/employee.c
        dal/query/employee.h
        dal/query/product.c
        dal/query/product.h
        dal/query/sales.c
        dal/query/sales.h
        dal/model/employee.h
        dal/model/product.h
        dal/model/sale.h)

if(SQLITE3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
    target_link_libraries(hdu_ctask ${SQLite3_LIBRARIES})
else()
    message(FATAL_ERROR "SQLite3 not found")
endif()


