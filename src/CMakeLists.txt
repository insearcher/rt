cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        main.c
        rt_render.c
        rt_render_processing.c
        rt_post_processing.c
        rt_sdf.c
        rt_sdf2.c
        rt_sdf3.c
        rt_system.c
        rt_input_system.c
        rt_physics_system.c
        rt_rotations.c
        rt_setup.c
        rt_get_texture.c
        rt_find_by_id.c
        rt_utilities.c
        )

add_subdirectory(rt_jtoc)
add_subdirectory(interface)
