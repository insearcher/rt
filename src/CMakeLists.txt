cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        main.c
        initialization.c
        ray_marching_render.c
        move_camera_by_key.c
        ../utilits_cl/math_vec.c
        )