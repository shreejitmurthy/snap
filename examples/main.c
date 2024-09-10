#define SNAP_IMPLEMENTATION
#include "snap.h"

int main() {
    snp_gfx_init((snp_window_args){
            .title = "Window",
            .width = 800,
            .height = 600,
            .clear_colour.hex = 0x334d4d
    });

    snp_camera camera = snp_camera_init();
    camera.zoom = 1.0f;
    snp_camera_setpos(&camera, 400, 300);

    snp_texture player_spritesheet = snp_texture_init("../examples/player.png");
    snp_quad player_quad = (snp_quad){0, 0, 64, 64};

    snp_texture knight = snp_texture_init("../examples/knight.png");

    snp_texture animals = snp_texture_init("../examples/animals.png");
    snp_quad kangaroo_quad = (snp_quad){1, 387, 32, 32};

    while (snp_gfx_window_open()) {
        snp_gfx_clear();

        snp_camera_attach(camera);

        snp_texture_draw((snp_texture_draw_args){
                .texture = player_spritesheet,
                .quad = player_quad,
                .x = 400,
                .y = 300,
        });

        snp_texture_draw((snp_texture_draw_args){
                .texture = knight,
                .x = 100,
                .y = 100,
                .sx = 2, .sy = 2
        });

        snp_camera_detach();

        snp_texture_draw((snp_texture_draw_args){
                .texture = animals,
                .quad = kangaroo_quad,
                .x = 500,
                .y = 400,
                .sx = 2, .sy = 2
        });

        snp_gfx_refresh();
    }

    snp_texture_delete(player_spritesheet);

    snp_gfx_destroy();
    return 0;
}
