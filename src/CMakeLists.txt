cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        main.c
        rt_render.c
        rt_sdf.c
        rt_raycast.c
        rt_system.c
        rt_input_system.c
        rt_physics_system.c
        rt_rotations.c
        )

add_subdirectory(rt_jtoc)
