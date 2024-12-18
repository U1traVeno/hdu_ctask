//
// Created by U1traVeno on 24-12-18.
//

#ifndef BASE_MODEL_H
#define BASE_MODEL_H

// 各个表通用字段结构体，包含ID, CreatedAt, UpdatedAt, DeletedAt, 用于嵌入到各个表的结构体中
typedef struct {
    int id;
    char* created_at;
    char* updated_at;
    char* deleted_at;
} BaseModel;

#endif //BASE_MODEL_H
