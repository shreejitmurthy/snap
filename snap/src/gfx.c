#include "gfx.h"
#include <assert.h>
#include <glad/glad.h>

void gfx_init(snp_window_args args) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "%s\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    state.win_args = args;
    state.quit = false;
    state.window = SDL_CreateWindow(state.win_args.title, state.win_args.width, state.win_args.height, SDL_WINDOW_OPENGL);
    assert(state.window);

    state.context = SDL_GL_CreateContext(state.window);
    assert(state.context);

    SDL_GL_SetSwapInterval(1);

    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0) {
        fprintf(stderr, "Failed to load GLAD\n");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, state.win_args.width, state.win_args.height);
}

bool gfx_window_open() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                state.quit = true;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE) {
                    state.quit = true;
                }
                break;
        }
    }

    return !state.quit;
}

void gfx_refresh() {
    // check if rgb values are zero/undefined
    if (state.win_args.clear_colour.r == 0 && state.win_args.clear_colour.g == 0 && state.win_args.clear_colour.b == 0) {
        // check if hex value is zero/undefined
        if (state.win_args.clear_colour.hex == 0x00000000) {
            glClearColor(0.f, 0.f, 0.f, 0.f);
        }
        // rgb value zero/undefined, hex value non-zero/defined
        else {
            float r = (state.win_args.clear_colour.hex >> 16) & 0xFF;
            float g = (state.win_args.clear_colour.hex >> 8) & 0xFF;
            float b = state.win_args.clear_colour.hex & 0xFF;

            glClearColor(r/255, g/255, b/255, 1.f);
        }
    }
    // rgb value prioritised over hex.
    else {
        glClearColor(state.win_args.clear_colour.r, state.win_args.clear_colour.g, state.win_args.clear_colour.b, 1.f);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(state.window);
}

void gfx_destroy() {
    SDL_GL_DestroyContext(state.context);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}
