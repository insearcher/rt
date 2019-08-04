cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        main.c
        rt_render.c
        rt_system.c
        rt_input_system.c
        rt_physics_system.c
        )