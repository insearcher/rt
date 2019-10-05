cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        uix_function_list.c
        button_selector.c
        uix_render_mode_choose.c
        uix_postprocessing_choose.c
        uix_popup_menu.c
        uix_init.c
        uix_fill_scene.c
        uix_fill_default_images.c
        uix_choose_obj_from_scene.c
        rt_uix_update_inspector.c
        )