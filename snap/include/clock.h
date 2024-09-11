//
// Created by Shreejit Murthy on 11/9/2024.
//

#pragma once
#include <stdint.h>

typedef struct {
    uint32_t last_time;
    uint32_t current_time;
    double delta_time;
    uint32_t frame_count;
    uint32_t fps_update_interval;
    uint32_t last_fps_update_time;
} snp_clock;

snp_clock snp_clock_init();
void snp_clock_tick(snp_clock* clock);
double snp_clock_get_delta(snp_clock clock);
//float snp_clock_get_fps(snp_clock* clock);
void snp_clock_reset(snp_clock* clock);
