cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(ui PUBLIC
        bfs_for_draw.c
        bfs_for_find_el_by_id.c
        bfs_for_raycast.c
        bfs_for_resize.c
        bfs_iter.c
        queue.c
        )