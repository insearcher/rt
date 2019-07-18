cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(ui PUBLIC
        ui_file_find_last_slash.c
        ui_file_open_file_dialog.c
        ui_file_parse_path.c
        ui_file_save_file_dialog.c
        ui_save_surface.c
        )