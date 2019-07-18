cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(ui PUBLIC
        ui_jtoc_el_from_json.c
        ui_jtoc_el_get_and_setup_json.c
        ui_jtoc_el_pref_modal_win.c
        ui_jtoc_el_pref_text.c
        ui_jtoc_main_from_json.c
        ui_jtoc_utils.c
        ui_jtoc_win_from_json.c
        ui_jtoc_create_modal_ok.c
        ui_jtoc_create_modal_ok_cancel.c
        ui_jtoc_efj_helper3.c
        ui_jtoc_efj_helper2.c
        ui_jtoc_efj_helper1.c
        ui_jtoc_pref_text_modal_win.c
        )
