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
        rt_jtoc_utilits2.c
        rt_jtoc_get_box.c
        rt_jtoc_get_cone.c
        rt_jtoc_get_cylinder.c
        rt_jtoc_get_plane.c
        rt_jtoc_get_round_box.c
        rt_jtoc_get_sphere.c
        rt_jtoc_get_torus.c
        rt_jtoc_get_object.c
        rt_jtoc_get_object_name.c
        rt_jtoc_get_object_layer.c
        rt_jtoc_get_object_type.c
        rt_jtoc_get_object_texture.c
        )
