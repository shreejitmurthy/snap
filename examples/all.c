#define SNAP_IMPLEMENTATION
#include "snap.h"

int main() {
    // Create the window's specifics
    snp_window_args args = {
            .title = "Window",
            .width = 800,
            .height = 600,
            .clear_colour = snp_hex_to_rgba(0x334d4d)  // Teal colour
    };

    // Initialise the system with the window arguments
    snp_system_init(args);

    // Create player sprite, with its own quad
    snp_texture player_spritesheet = snp_texture_init("../examples/player.png");
    snp_quad player_quad = (snp_quad){0, 0, 64, 64};
    snp_vec2 player_position = {400, 300};

    snp_camera camera = snp_camera_init();
    camera.zoom = 1.5f;
    snp_camera_setpos(&camera, player_position);

    snp_texture knight = snp_texture_init("../examples/knight.png");

    snp_texture animals = snp_texture_init("../examples/animals.png");
    snp_quad kangaroo_quad = (snp_quad){1, 387, 32, 32};

    snp_texture health_bar = snp_texture_init("../examples/healthbar.png");

    // Create a (very basic) clock.
    snp_clock clock = snp_clock_init();

    while (snp_gfx_window_open()) {
        snp_gfx_clear();

        // Tick (update) the clock and get the time between frames (delta time)
        snp_clock_tick(&clock);
        double dt = snp_clock_get_delta(clock);

        if (snp_keyboard_down(SNPK_ESCAPE)) {
            snp_app_state.window_open = false;
        }

        // Update player position with keyboard
        if (snp_keyboard_down(SNPK_A)) {
            player_position.x -= 100.f * dt;
        } else if (snp_keyboard_down(SNPK_D)) {
            player_position.x += 100.f * dt;
        }

        if (snp_keyboard_down(SNPK_W)) {
            player_position.y -= 100.f * dt;
        } else if (snp_keyboard_down(SNPK_S)) {
            player_position.y += 100.f * dt;
        }

        snp_camera_setpos(&camera, player_position);

        snp_camera_attach(camera);  // Attach the camera

        snp_texture_draw((snp_texture_draw_args){
                .texture = knight,
                .position = {200, 300},
                .sx = 2, .sy = 2
        });

        snp_texture_draw((snp_texture_draw_args){
                .texture = animals,
                .quad = kangaroo_quad,
                .position = {500, 400},
                .sx = 2, .sy = 2
        });

        // Draw the player last to ensure it's on top.
        // - also draw with quad to only get a portion of the image
        snp_texture_draw((snp_texture_draw_args){
                .texture = player_spritesheet,
                .quad = player_quad,
                .position = player_position
        });

        snp_camera_detach();  // Detach the camera, everything drawn within the attach/detach zone are 'in the world'

        // Health bar UI to be drawn over the top, not 'in the world'
        snp_texture_draw((snp_texture_draw_args){
                .texture = health_bar,
                .position = {75, 25},
                .sx = 2, .sy = 2
        });

        snp_gfx_refresh();
    }

    // Delete textures.
    snp_texture_delete(player_spritesheet);
    snp_texture_delete(knight);
    snp_texture_delete(animals);
    snp_texture_delete(health_bar);

    snp_gfx_destroy();
    return 0;
}
