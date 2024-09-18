#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "shader.h"
#include "vec.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    float r, g, b, a;
} snp_colour;  // with a 'u'!

snp_colour snp_hex_to_rgba(uint32_t hex);

typedef struct {
    const char* title;
    int width, height;
    snp_colour clear_colour;
    bool log;
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
    snp_vec2 position;
    snp_quad quad;
    float sx, sy;
    snp_colour tint;
} snp_texture_draw_args;

typedef struct {
    snp_shader shader;
    float zoom;
    vec2 position;
    mat4 projection;
    mat4 view;
} snp_camera;

typedef struct {
    unsigned int ID;       // ID handle of the glyph texture
    ivec2 size;            // Size of glyph
    ivec2 bearing;         // Offset from baseline to left/top of glyph
    unsigned int advance;  // Offset to advance to next glyph
} snp_character;

struct {
    snp_window_args win_args;
    SDL_Window* win;
    SDL_GLContext ctx;
    bool window_open;
    snp_shader texture_shader;
} snp_app_state;

void snp_gfx_init(snp_window_args args);
bool snp_gfx_window_open();
void snp_gfx_refresh();
void snp_gfx_clear();
void snp_gfx_destroy();

snp_texture snp_texture_init(const char* path);
void snp_texture_apply_quad(snp_texture* texture, snp_quad quad);
void snp_texture_gen_buffers(snp_texture* texture);
void snp_texture_updateVBO(snp_texture texture);
void snp_texture_draw(snp_texture_draw_args args);
void snp_texture_delete(snp_texture texture);

snp_camera snp_camera_init();
void snp_camera_setpos(snp_camera* camera, snp_vec2 position);
void snp_camera_get_view(snp_camera* camera);
void snp_camera_get_proj(snp_camera* camera);
void snp_camera_attach(snp_camera camera);
void snp_camera_detach();

#ifdef __cplusplus
}
#endif
