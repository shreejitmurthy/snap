//
// Created by Shreejit Murthy on 10/9/2024.
//

#include "keyboard.h"
#include <SDL3/SDL_keycode.h>
#include <log/src/log.h>

const uint32_t SNPK_ESCAPE  =  SDLK_ESCAPE;
const uint32_t SNPK_0       =  SDLK_0;
const uint32_t SNPK_1       =  SDLK_1;
const uint32_t SNPK_2       =  SDLK_2;
const uint32_t SNPK_3       =  SDLK_3;
const uint32_t SNPK_4       =  SDLK_4;
const uint32_t SNPK_5       =  SDLK_5;
const uint32_t SNPK_6       =  SDLK_6;
const uint32_t SNPK_7       =  SDLK_7;
const uint32_t SNPK_8       =  SDLK_8;
const uint32_t SNPK_9       =  SDLK_9;
const uint32_t SNPK_A       =  SDLK_A;
const uint32_t SNPK_B       =  SDLK_B;
const uint32_t SNPK_C       =  SDLK_C;
const uint32_t SNPK_D       =  SDLK_D;
const uint32_t SNPK_E       =  SDLK_E;
const uint32_t SNPK_F       =  SDLK_F;
const uint32_t SNPK_G       =  SDLK_G;
const uint32_t SNPK_H       =  SDLK_H;
const uint32_t SNPK_I       =  SDLK_I;
const uint32_t SNPK_J       =  SDLK_J;
const uint32_t SNPK_K       =  SDLK_K;
const uint32_t SNPK_L       =  SDLK_L;
const uint32_t SNPK_M       =  SDLK_M;
const uint32_t SNPK_N       =  SDLK_N;
const uint32_t SNPK_O       =  SDLK_O;
const uint32_t SNPK_P       =  SDLK_P;
const uint32_t SNPK_Q       =  SDLK_Q;
const uint32_t SNPK_R       =  SDLK_R;
const uint32_t SNPK_S       =  SDLK_S;
const uint32_t SNPK_T       =  SDLK_T;
const uint32_t SNPK_U       =  SDLK_U;
const uint32_t SNPK_V       =  SDLK_V;
const uint32_t SNPK_W       =  SDLK_W;
const uint32_t SNPK_X       =  SDLK_X;
const uint32_t SNPK_Y       =  SDLK_Y;
const uint32_t SNPK_Z       =  SDLK_Z;
const uint32_t SNPK_F1      =  SDLK_F1;
const uint32_t SNPK_F2      =  SDLK_F2;
const uint32_t SNPK_F3      =  SDLK_F3;
const uint32_t SNPK_F4      =  SDLK_F4;
const uint32_t SNPK_F5      =  SDLK_F5;
const uint32_t SNPK_F6      =  SDLK_F6;
const uint32_t SNPK_F7      =  SDLK_F7;
const uint32_t SNPK_F8      =  SDLK_F8;
const uint32_t SNPK_F9      =  SDLK_F9;
const uint32_t SNPK_F10     =  SDLK_F10;
const uint32_t SNPK_F11     =  SDLK_F11;
const uint32_t SNPK_F12     =  SDLK_F12;
const uint32_t SNPK_TAB     =  SDLK_TAB;
const uint32_t SNPK_SPACE   =  SDLK_SPACE;


void snp_keyboard_init() {
    for(int i = 0; i < 322; i++) {  // init them all to false
        KEYS[i] = false;
    }
    log_info("SNP::Initialised keyboard");
}

void snp_keyboard_process(SDL_Event event) {
    if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
        if (event.key.scancode < SDL_NUM_SCANCODES) {
            KEYS[event.key.scancode] = (event.type == SDL_EVENT_KEY_DOWN);
        }
    }
}

bool snp_keyboard_down(uint32_t key) {
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, 0);
    return (scancode < SDL_NUM_SCANCODES && KEYS[scancode]);
}
