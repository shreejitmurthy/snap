//
// Created by Shreejit Murthy on 11/9/2024.
//

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    float x, y;
} snp_vec2;

typedef struct {
    float x, y, z;
} snp_vec3;

typedef struct {
    float x, y, z, w;
} snp_vec4;

#ifdef __cplusplus
}
#endif
