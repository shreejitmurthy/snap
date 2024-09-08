//
// Created by Shreejit Murthy on 7/9/2024.
//

#pragma once
#include <cglm/cglm.h>

typedef struct {
    unsigned int ID;
} snp_shader;

typedef struct {
    const char* vertex_path;
    const char* fragment_path;
} snp_shader_args;

snp_shader snp_shader_init(snp_shader_args args);
void snp_shader_use(snp_shader shader);
void snp_shader_set_mat4(snp_shader shader, const char* name, mat4 mat);