cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(ui PUBLIC
        ui_sdl_init.c
        ui_sdl_deinit.c
        ui_sdl_set_render.c
        ui_sdl_set_texture_mode.c
        ui_sdl_render.c
        ui_sdl_render_draw.c
        ui_sdl_texture.c
        ui_sdl_win_position.c
        ui_sdl_surface.c
        )