#pragma once

#ifdef SNAP_IMPLEMENTATION
#include <SDL3/SDL_main.h>
#endif // SNAP_IMPLEMENTATION

#ifdef __cplusplus
extern "C"
{
#endif

#include "keyboard.h"
#include "gfx.h"
#include "shader.h"
#include "clock.h"

    void snp_system_init(snp_window_args win_args) {
        snp_gfx_init(win_args);
        snp_keyboard_init();
    }

#ifdef __cplusplus
}
#endif