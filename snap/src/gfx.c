#include "gfx.h"
#include <assert.h>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "keyboard.h"
#include <log/log.h>

/*
   _________        .__
   \_   ___ \  ____ |  |   ____  __ _________
   /    \  \/ /  _ \|  |  /  _ \|  |  \_  __ \
   \     \___(  <_> )  |_(  <_> )  |  /|  | \/
    \______  /\____/|____/\____/|____/ |__|
           \/
 */

snp_colour snp_hex_to_rgba(uint32_t hex) {
    snp_colour colour;
    colour.r = ((hex >> 16) & 0xFF) / 255.0f;
    colour.g = ((hex >> 8) & 0xFF) / 255.0f;
    colour.b = (hex & 0xFF) / 255.0f;
    return colour;
}

bool is_zero_colour(snp_colour colour) {
    return !(colour.r || colour.g || colour.b || colour.a);
}

/*
   _________
   \_   ___ \  ___________   ____
   /    \  \/ /  _ \_  __ \_/ __ \
   \     \___(  <_> )  | \/\  ___/
    \______  /\____/|__|    \___  >
           \/                   \/
 */

void snp_gfx_init(snp_window_args args) {
    log_set_quiet(!args.log);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        log_error("SNP::Initialise Error: %s", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    snp_app_state.win_args = args;
    snp_app_state.window_open = true;
    snp_app_state.win = SDL_CreateWindow(snp_app_state.win_args.title, snp_app_state.win_args.width, snp_app_state.win_args.height, SDL_WINDOW_OPENGL);
    assert(snp_app_state.win);

    snp_app_state.ctx = SDL_GL_CreateContext(snp_app_state.win);
    assert(snp_app_state.ctx);

    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) == 0) {
        log_error("SNP::Failed to initialise GLAD");
    }

    SDL_GL_SetSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, snp_app_state.win_args.width, snp_app_state.win_args.height);

    snp_app_state.texture_shader = snp_shader_init((snp_shader_args){
            .vertex_path = "../snap/shaders/texture.vert",
            .fragment_path = "../snap/shaders/texture.frag"
    });

    log_info("SNP::Initialised GFX");
}

bool snp_gfx_window_open() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                snp_app_state.window_open = false;
                break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                snp_keyboard_process(event);
                break;

            default:
                break;
        }
    }

    return snp_app_state.window_open;
}

void snp_gfx_refresh() {
    SDL_GL_SwapWindow(snp_app_state.win);
}

void snp_gfx_clear() {
    glClearColor(snp_app_state.win_args.clear_colour.r, snp_app_state.win_args.clear_colour.g, snp_app_state.win_args.clear_colour.b, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
}

void snp_gfx_destroy() {
    SDL_GL_DestroyContext(snp_app_state.ctx);
    SDL_DestroyWindow(snp_app_state.win);
    log_info("SNP::Destroyed GFX");
    SDL_Quit();
    log_info("SNP::Goodbye!");
}

/*
   ___________              __
   \__    ___/___ ___  ____/  |_ __ _________   ____
     |    |_/ __ \\  \/  /\   __\  |  \_  __ \_/ __ \
     |    |\  ___/ >    <  |  | |  |  /|  | \/\  ___/
     |____| \___  >__/\_ \ |__| |____/ |__|    \___  >
                \/      \/                         \/
 */

snp_texture snp_texture_init(const char* path) {
    snp_texture texture;
    texture.shader = snp_app_state.texture_shader;
    glGenTextures(1, &texture.ID);
    glBindTexture(GL_TEXTURE_2D, texture.ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    unsigned char* data = stbi_load(path, &texture.width, &texture.height, &texture.nr_channels, 4);
    if (data) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        log_error("SNP::Failed to load texture at %s", path);
    }

    snp_quad quad = (snp_quad){0, 0, (float)texture.width, (float)texture.height};

    snp_texture_apply_quad(&texture, quad);

    unsigned int i[6] = {
            0, 1, 3,  // first triangle
            1, 2, 3   // second triangle
    };

    memcpy(texture.indices, i, sizeof(i));

    snp_texture_gen_buffers(&texture);

    log_info("SNP::Loaded texture at %s", path);

    return texture;
}

void snp_texture_apply_quad(snp_texture* texture, snp_quad quad) {
    texture->quad = quad;
    float u0 = texture->quad.x / texture->width;
    float v0 = texture->quad.y / texture->height;
    float u1 = (texture->quad.x + texture->quad.w) / texture->width;
    float v1 = (texture->quad.y + texture->quad.h) / texture->height;

    float halfWidth  = texture->quad.w / 2.0f;
    float halfHeight = texture->quad.h / 2.0f;

    float v[32] = {
            /*     positions         tx coords        colors     */
            halfWidth,  halfHeight,   u1, v1,    1.0f, 0.0f, 0.0f,  // top right
            halfWidth,  -halfHeight,  u1, v0,    0.0f, 1.0f, 0.0f,  // bottom right
            -halfWidth, -halfHeight,  u0, v0,    0.0f, 0.0f, 1.0f,  // bottom left
            -halfWidth, halfHeight,   u0, v1,    1.0f, 1.0f, 0.0f   // top left
    };

    memcpy(texture->vertices, v, sizeof(v));
}

void snp_texture_gen_buffers(snp_texture* texture) {
    // Generate and bind VAO, VBO, and EBO
    glGenVertexArrays(1, &texture->VAO);
    glGenBuffers(1, &texture->VBO);
    glGenBuffers(1, &texture->EBO);

    glBindVertexArray(texture->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, texture->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture->vertices), texture->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texture->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(texture->indices), texture->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

void snp_texture_updateVBO(snp_texture texture) {
    glBindBuffer(GL_ARRAY_BUFFER, texture.VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(texture.vertices), texture.vertices);
}

void snp_texture_draw(snp_texture_draw_args args) {
    if (args.quad.w == 0.0f) {
        args.quad = (snp_quad){0, 0, args.texture.width, args.texture.height};
    }
    snp_texture_apply_quad(&args.texture, args.quad);
    snp_texture_updateVBO(args.texture);

    vec2 position = {args.position.x, args.position.y};
    mat4 model;
    glm_mat4_identity(model);

    vec3 translation = {position[0], position[1], 0.0f};
    glm_translate(model, translation);
    vec3 finalScale = {args.sx == 0 ? 1.0f : args.sx, args.sy == 0 ? 1.0f : args.sy, 1.0f};
    glm_scale(model, finalScale);

    snp_shader_use(snp_app_state.texture_shader);
    snp_shader_set_mat4(snp_app_state.texture_shader, "model", model);
    vec4 tint;
    glm_vec4_copy(
            is_zero_colour(args.tint) ? (vec4){1.0f, 1.0f, 1.0f, 1.0f} : (vec4){args.tint.r, args.tint.g, args.tint.b, args.tint.a},
            tint
    );
    snp_shader_set_vec4(snp_app_state.texture_shader, "tint", tint);

    glBindTexture(GL_TEXTURE_2D, args.texture.ID);
    glBindVertexArray(args.texture.VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void snp_texture_delete(snp_texture texture) {
    glDeleteTextures(1, &texture.ID);
}

/*
   _________
   \_   ___ \_____    _____   ________________
   /    \  \/\__  \  /     \_/ __ \_  __ \__  \
   \     \____/ __ \|  Y Y  \  ___/|  | \// __ \_
    \______  (____  /__|_|  /\___  >__|  (____  /
           \/     \/      \/     \/           \/
 */

snp_camera snp_camera_init() {
    snp_camera camera;
    glm_mat4_zero(camera.projection);
    glm_mat4_zero(camera.view);
    camera.zoom = 1.0f;
    glm_vec2_zero(camera.position);
    log_info("SNP::Initialised camera");
    return camera;
}

void snp_camera_setpos(snp_camera* camera, snp_vec2 position) {
    glm_vec2_copy((vec2){position.x, position.y}, camera->position);
}

void snp_camera_get_view(snp_camera* camera) {
    vec3 camera_pos = {0.0f, 0.0f, 1.0f};
    vec3 target_pos = {0.0f, 0.0f, 0.0f};
    vec3 up_vector  = {0.0f, 1.0f, 0.0f};

    glm_lookat(camera_pos, target_pos, up_vector, camera->view);
}

void snp_camera_get_proj(snp_camera* camera) {
    float left   = camera->position[0] - (snp_app_state.win_args.width  / 2.0f) / camera->zoom;
    float right  = camera->position[0] + (snp_app_state.win_args.width  / 2.0f) / camera->zoom;
    float top    = camera->position[1] - (snp_app_state.win_args.height / 2.0f) / camera->zoom;
    float bottom = camera->position[1] + (snp_app_state.win_args.height / 2.0f) / camera->zoom;

    glm_ortho(left, right, bottom, top, -1.0f, 1.0f, camera->projection);
}

void snp_camera_attach(snp_camera camera) {
    snp_camera_get_proj(&camera);
    snp_camera_get_view(&camera);
    snp_shader_set_mat4(snp_app_state.texture_shader, "view", camera.view);
    snp_shader_set_mat4(snp_app_state.texture_shader, "projection", camera.projection);
}

void snp_camera_detach() {
    mat4 proj;
    mat4 view;
    glm_mat4_identity(view);
    glm_ortho(0.0f, snp_app_state.win_args.width, snp_app_state.win_args.height, 0.0f, -1.0f, 1.0f, proj);
    snp_shader_set_mat4(snp_app_state.texture_shader, "projection", proj);
    snp_shader_set_mat4(snp_app_state.texture_shader, "view", view);
}

/*
   ___________               __
   \_   _____/____    ____ _/  |_
    |    __) /  _ \  /    \\   __\
    |     \ (  <_> )|   |  \|  |
    \___  /  \____/ |___|  /|__|
        \/               \/
 */


