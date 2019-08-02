cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        main.c
        move_camera_by_key.c
        rt_render.c
        rt_physics_system.c
        )