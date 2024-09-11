//
// Created by Shreejit Murthy on 10/9/2024.
//

#include "keyboard.h"
#include <SDL3/SDL_keycode.h>

const uint32_t SNPK_ESCAPE  =  0x0000001bu;
const uint32_t SNPK_2       =  0x00000032u;
const uint32_t SNPK_3       =  0x00000033u;
const uint32_t SNPK_4       =  0x00000034u;
const uint32_t SNPK_5       =  0x00000035u;
const uint32_t SNPK_6       =  0x00000036u;
const uint32_t SNPK_7       =  0x00000037u;
const uint32_t SNPK_8       =  0x00000038u;
const uint32_t SNPK_9       =  0x00000039u;
const uint32_t SNPK_A       =  0x00000061u;
const uint32_t SNPK_B       =  0x00000062u;
const uint32_t SNPK_C       =  0x00000063u;
const uint32_t SNPK_D       =  0x00000064u;
const uint32_t SNPK_E       =  0x00000065u;
const uint32_t SNPK_F       =  0x00000066u;
const uint32_t SNPK_G       =  0x00000067u;
const uint32_t SNPK_H       =  0x00000068u;
const uint32_t SNPK_I       =  0x00000069u;
const uint32_t SNPK_J       =  0x0000006au;
const uint32_t SNPK_K       =  0x0000006bu;
const uint32_t SNPK_L       =  0x0000006cu;
const uint32_t SNPK_M       =  0x0000006du;
const uint32_t SNPK_N       =  0x0000006eu;
const uint32_t SNPK_O       =  0x0000006fu;
const uint32_t SNPK_P       =  0x00000070u;
const uint32_t SNPK_Q       =  0x00000071u;
const uint32_t SNPK_R       =  0x00000072u;
const uint32_t SNPK_S       =  0x00000073u;
const uint32_t SNPK_T       =  0x00000074u;
const uint32_t SNPK_U       =  0x00000075u;
const uint32_t SNPK_V       =  0x00000076u;
const uint32_t SNPK_W       =  0x00000077u;
const uint32_t SNPK_X       =  0x00000078u;
const uint32_t SNPK_Y       =  0x00000079u;
const uint32_t SNPK_Z       =  0x0000007au;
const uint32_t SNPK_F1      =  0x4000003au;
const uint32_t SNPK_F2      =  0x4000003bu;
const uint32_t SNPK_F3      =  0x4000003cu;
const uint32_t SNPK_F4      =  0x4000003du;
const uint32_t SNPK_F5      =  0x4000003eu;
const uint32_t SNPK_F6      =  0x4000003fu;
const uint32_t SNPK_F7      =  0x40000040u;
const uint32_t SNPK_F8      =  0x40000041u;
const uint32_t SNPK_F9      =  0x40000042u;
const uint32_t SNPK_F10     =  0x40000043u;
const uint32_t SNPK_F11     =  0x40000044u;
const uint32_t SNPK_F12     =  0x40000045u;
const uint32_t SNPK_TAB     =  0x00000009u;
const uint32_t SNPK_SPACE   =  0x00000020u;
const uint32_t SNPK_0       =  0x00000030u;
const uint32_t SNPK_1       =  0x00000031u;


void snp_keyboard_init() {
    for(int i = 0; i < 322; i++) {  // init them all to false
        KEYS[i] = false;
    }
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
