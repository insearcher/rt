cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        uix_function_list.c
        button_selector.c
        uix_render_mode_choose.c
        uix_posprocessing_choose.c
        )