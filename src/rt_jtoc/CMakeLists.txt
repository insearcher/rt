cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        rt_jtoc_get_camera.c
        rt_jtoc_get_lights.c
        rt_jtoc_get_objects.c
        rt_jtoc_ps_setup.c
        rt_jtoc_get_objects_params.c
        rt_jtoc_get_textures.c
        rt_jtoc_get_transform.c
        rt_jtoc_scene_setup.c
        rt_jtoc_utilits.c
        )
