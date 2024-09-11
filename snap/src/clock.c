//
// Created by Shreejit Murthy on 11/9/2024.
//

#include "clock.h"
#include <SDL3/SDL_timer.h>

snp_clock snp_clock_init() {
    snp_clock clock;
    clock.current_time = SDL_GetTicks();
    clock.last_time = clock.current_time;
    clock.delta_time = 0.0f;
    return clock;
}

void snp_clock_tick(snp_clock* clock) {
    clock->last_time = clock->current_time;
    clock->current_time = SDL_GetTicks();
    clock->delta_time = (clock->current_time - clock->last_time) / 1000.0f;
    clock->frame_count++;
}

double snp_clock_get_delta(snp_clock clock) {
    return clock.delta_time;
}

//float snp_clock_get_fps(snp_clock* clock) {
//    float fps = 0;
//    if (SDL_GetTicks() - clock->last_fps_update_time >= clock->fps_update_interval) {
//        fps = clock->frame_count * 1000.0f / (SDL_GetTicks() - clock->last_fps_update_time);
//        printf("FPS: %f\n", fps);
//
//        // Reset for the next interval
//        clock->last_fps_update_time = SDL_GetTicks();
//        clock->frame_count = 0;
//    }
//
//    return fps;
//}

void snp_clock_reset(snp_clock* clock) {
    clock->current_time = SDL_GetTicks();
    clock->last_time = clock->current_time;
    clock->delta_time = 0.0f;
}
