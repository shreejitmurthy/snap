#define SNAP_IMPLEMENTATION
#include "snap.h"

int main() {
    gfx_init((snp_window_args){
        .title = "Window",
        .width = 800,
        .height = 600,
        .clear_colour.hex = 0x6495ED
    });

    while (gfx_window_open()) {

        gfx_refresh();
    }

    gfx_destroy();
    return 0;
}