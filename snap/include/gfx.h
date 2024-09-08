#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "shader.h"

#ifdef SNAP_IMPLEMENTATION
#include <SDL3/SDL_main.h>
#endif // SNAP_IMPLEMENTATION

typedef struct {
    float r, g, b, a;
    uint32_t hex;
} snp_colour;  // with a 'u'!

typedef struct {
    const char* title;
    int width, height;
    snp_colour clear_colour;
} snp_window_args;

typedef struct {
    float x, y, w, h;
} snp_quad;

typedef struct {
    unsigned int ID;
    unsigned int VAO, VBO, EBO;
    float vertices[32];
    unsigned int indices[6];
    int width, height, nr_channels;
    snp_quad quad;
    snp_shader shader;
} snp_texture;

typedef struct {
    snp_texture texture;
    float x, y;
    snp_quad quad;
    float sx, sy;
} snp_texture_draw_args;


struct {
    snp_window_args win_args;
    SDL_Window* window;
    SDL_GLContext context;
    bool quit;
    snp_shader texture_shader;
} state;

void gfx_init(snp_window_args args);
bool gfx_window_open();
void gfx_refresh();
void gfx_clear();
void gfx_destroy();

snp_texture snp_texture_init(const char* path);
void snp_texture_apply_quad(snp_texture* texture, snp_quad quad);
void snp_texture_gen_buffers(snp_texture* texture);
void snp_texture_updateVBO(snp_texture texture);
void snp_texture_draw(snp_texture_draw_args args);
void snp_texture_delete(snp_texture texture);
