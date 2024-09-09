#define SNAP_IMPLEMENTATION
#include "snap.h"

int main() {
    snp_gfx_init((snp_window_args){
        .title = "Window",
        .width = 800,
        .height = 600,
        .clear_colour.hex = 0x6495ED
    });

    snp_camera camera = snp_camera_init();
    camera.zoom = 1.0f;
    snp_camera_setpos(&camera, 200, 300);  // offset camera slightly from centre to show effect

    snp_texture texture = snp_texture_init("../examples/player_sprite_borderless.png");
    snp_quad quad = (snp_quad){16, 0, 16, 32};

    while (snp_gfx_window_open()) {
        snp_gfx_clear();

        snp_camera_attach(camera);

        snp_texture_draw((snp_texture_draw_args){
            .texture = texture,
            .quad = quad,
            .x = 400,
            .y = 300,
            .sx = 2, .sy = 2
        });

        snp_camera_detach(camera);

        snp_gfx_refresh();
    }

    snp_texture_delete(texture);

    snp_gfx_destroy();
    return 0;
}