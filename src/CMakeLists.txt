cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(rt PUBLIC
        test.c
        initialization.c
        initialization_cl.c
        main.c
        utilits_for_initialization_cl.c
        )