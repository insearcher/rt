cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(ui PUBLIC
        ui_win_create.c
        ui_win_destroy.c
        ui_win_event_change_text_in_focused_el.c
        ui_win_event_focus.c
        ui_win_event_update_size.c
        ui_win_find_el_by_id.c
        ui_win_init.c
        ui_win_setup_default.c
        )
