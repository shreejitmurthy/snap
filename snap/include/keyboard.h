//
// Created by Shreejit Murthy on 10/9/2024.
//

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#ifdef __cplusplus
extern "C"
{
#endif

bool KEYS[322];

extern const uint32_t SNPK_ESCAPE;
extern const uint32_t SNPK_2;
extern const uint32_t SNPK_3;
extern const uint32_t SNPK_4;
extern const uint32_t SNPK_5;
extern const uint32_t SNPK_6;
extern const uint32_t SNPK_7;
extern const uint32_t SNPK_8;
extern const uint32_t SNPK_9;
extern const uint32_t SNPK_A;
extern const uint32_t SNPK_B;
extern const uint32_t SNPK_C;
extern const uint32_t SNPK_D;
extern const uint32_t SNPK_E;
extern const uint32_t SNPK_F;
extern const uint32_t SNPK_G;
extern const uint32_t SNPK_H;
extern const uint32_t SNPK_I;
extern const uint32_t SNPK_J;
extern const uint32_t SNPK_K;
extern const uint32_t SNPK_L;
extern const uint32_t SNPK_M;
extern const uint32_t SNPK_N;
extern const uint32_t SNPK_O;
extern const uint32_t SNPK_P;
extern const uint32_t SNPK_Q;
extern const uint32_t SNPK_R;
extern const uint32_t SNPK_S;
extern const uint32_t SNPK_T;
extern const uint32_t SNPK_U;
extern const uint32_t SNPK_V;
extern const uint32_t SNPK_W;
extern const uint32_t SNPK_X;
extern const uint32_t SNPK_Y;
extern const uint32_t SNPK_Z;
extern const uint32_t SNPK_F1;
extern const uint32_t SNPK_F2;
extern const uint32_t SNPK_F3;
extern const uint32_t SNPK_F4;
extern const uint32_t SNPK_F5;
extern const uint32_t SNPK_F6;
extern const uint32_t SNPK_F7;
extern const uint32_t SNPK_F8;
extern const uint32_t SNPK_F9;
extern const uint32_t SNPK_F10;
extern const uint32_t SNPK_F11;
extern const uint32_t SNPK_F12;
extern const uint32_t SNPK_TAB;
extern const uint32_t SNPK_SPACE;
extern const uint32_t SNPK_0;
extern const uint32_t SNPK_1;

void snp_keyboard_init();
void snp_keyboard_process(SDL_Event event);
bool snp_keyboard_down(uint32_t key);

#ifdef __cplusplus
}
#endif
