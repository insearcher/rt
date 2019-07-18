cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(ui PUBLIC
        ui_util_check_texture_id.c
        ui_util_get_pixel_color_from_el.c
        ui_util_get_pixel_color_from_texture.c
        ui_util_get_rect_from_frect.c
        ui_util_get_sdl_color.c
        ui_util_set_pixel_color_to_texture.c
        ui_surface_pixel.c
        )
