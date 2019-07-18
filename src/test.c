

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "rt.h"

//TODO ПЕРЕНЕСТИ ui_main_fill_default_functions в libui из сурсов гуимпа.



int main(void) {
    ui_sdl_init();
    t_ui_main *m = ui_main_init();

    ui_main_add_function_by_id(m, ray_marching, "ray_marching");
    ui_jtoc_main_from_json(m, "json/main.json");
    ui_main_run_program(m);
	return 0;
}