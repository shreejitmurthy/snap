#define SNAP_IMPLEMENTATION
#include "snap.h"

int main() {
    gfx_init((snp_window_args){
        .title = "Window",
        .width = 800,
        .height = 600,
        .clear_colour.hex = 0x6495ED
    });

    snp_texture texture = snp_texture_init("../examples/player_sprite_borderless.png");
    snp_quad quad = (snp_quad){16, 0, 16, 32};

    while (gfx_window_open()) {
        gfx_clear();

        snp_texture_draw((snp_texture_draw_args){
            .texture = texture,
            .quad = quad,
            .x = 400,
            .y = 300,
            .sx = 2, .sy = 2
        });

        gfx_refresh();
    }

    gfx_destroy();
    return 0;
}