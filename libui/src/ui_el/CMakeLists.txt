cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

target_sources(ui PUBLIC
        ui_el_add_child.c
        ui_el_add_texture.c
        ui_el_add_texture_from_main_by_id.c
        ui_el_change_pos.c
        ui_el_change_size.c
        ui_el_create_texture.c
        ui_el_create_texture_from_surface.c
        ui_el_destroy.c
        ui_el_destroy_children.c
        ui_el_event_children_set_default.c
        ui_el_event_default_draw.c
        ui_el_event_default_pointer_enter.c
        ui_el_event_default_pointer_exit.c
        ui_el_event_default_resize.c
        ui_el_event_drag.c
        ui_el_event_menu_resize.c
        ui_el_event_scroll_menu.c
        ui_el_event_set_texture.c
        ui_el_event_show_child.c
        ui_el_event_switch_radio.c
        ui_el_get_current_texture.c
        ui_el_get_texture_by_id.c
        ui_el_init.c
        ui_el_load_surface_from.c
        ui_el_set_current_texture_by_id.c
        ui_el_set_new_pos.c
        ui_el_set_new_size.c
        ui_el_set_pos.c
        ui_el_set_rel_pos.c
        ui_el_set_rel_size.c
        ui_el_set_size.c
        ui_el_set_text.c
        ui_el_setup_default.c
        ui_el_setup_default_draggable.c
        ui_el_setup_default_resizable.c
        ui_el_setup_default_scroll_menu.c
        ui_el_setup_default_scroll_menu_elem.c
        ui_el_setup_horizontal_draggable.c
        ui_el_setup_menu_resizable.c
        ui_el_setup_radio.c
        ui_el_update_text.c
        ui_el_event_close_window.c
        ui_el_event_show_window.c
        ui_el_remove_texture_by_id.c
        ui_el_utils_from_default_draw.c
        )