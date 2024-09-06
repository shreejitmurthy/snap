#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

struct {
    snp_window_args win_args;
    SDL_Window* window;
    SDL_GLContext context;
    bool quit;
} state;

void gfx_init(snp_window_args args);
bool gfx_window_open();
void gfx_refresh();
void gfx_destroy();
