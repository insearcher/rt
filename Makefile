# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/01 16:53:16 by sbednar           #+#    #+#              #
#    Updated: 2019/12/01 17:09:09 by sbednar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include				Makefile.inc

NAME			=	rt

TEXT_R			=	\033[0m
TEXT_B			=	\033[1m
TEXT_BL			=	\033[5m
TEXT_CR			=	\033[31m
TEXT_CG			=	\033[32m
TEXT_CY			=	\033[33m
TEXT_CB			=	\033[34m
TEXT_CM			=	\033[35m
TEXT_CC			=	\033[36m

FT_DIR			=	./libft
UI_DIR			=	./libui
CL_DIR			=	./libcl
JTOC_DIR		=	./libjtoc

INC_FT			=	$(FT_DIR)/include
INC_UI			=	$(UI_DIR)/include
INC_CL			=	$(CL_DIR)/include
INC_JTOC		=	$(JTOC_DIR)/include
INC_DIR			=	./include

SRC_DIR			=	./src
OBJ_DIR			=	./obj

SRC				=	main.c \
					rt_render.c \
					rt_render_processing.c \
					rt_post_processing.c \
					rt_sdf.c \
					rt_sdf2.c \
					rt_sdf3.c \
					rt_system.c \
					rt_input_system.c \
					rt_physics_system.c \
					rt_rotations.c \
					rt_setup.c \
					rt_get_texture.c \
					rt_find_by_id.c \
					rt_utilities.c \
					move_active.c \
					rotate_active.c

SRC_INTERFACE	=	uix_function_list.c \
					button_selector.c \
					uix_render_mode_choose.c \
					uix_postprocessing_choose.c \
					uix_popup_menu.c \
					uix_init.c \
					uix_fill_scene.c \
					uix_fill_default_images.c \
					uix_choose_obj_from_scene.c \
					rt_uix_update_inspector.c \
					uix_inspector_change_pos_button.c

SRC_JTOC		=	rt_jtoc_get_camera.c \
					rt_jtoc_get_lights.c \
					rt_jtoc_get_objects.c \
					rt_jtoc_ps_setup.c \
					rt_jtoc_get_objects_params.c \
					rt_jtoc_get_textures.c \
					rt_jtoc_get_transform.c \
					rt_jtoc_scene_setup.c \
					rt_jtoc_utilits.c \
					rt_jtoc_utilits2.c \
					rt_jtoc_get_box.c \
					rt_jtoc_get_cone.c \
					rt_jtoc_get_cylinder.c \
					rt_jtoc_get_plane.c \
					rt_jtoc_get_round_box.c \
					rt_jtoc_get_sphere.c \
					rt_jtoc_get_torus.c \
					rt_jtoc_get_object.c \
					rt_jtoc_get_object_name.c \
					rt_jtoc_get_object_layer.c \
					rt_jtoc_get_object_type.c \
					rt_jtoc_get_object_texture.c \
					rt_jtoc_get_lights_helper.c

OBJ				=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o)) \
					$(addprefix $(OBJ_DIR)/,$(SRC_INTERFACE:.c=.o)) \
					$(addprefix $(OBJ_DIR)/,$(SRC_JTOC:.c=.o))

INCS			=	-I$(INC_DIR) \
					-I$(INC_FT) \
					-I$(INC_UI) \
					-I$(INC_CL) \
					-I$(INC_JTOC) \
					-I./frameworks/SDL2.framework/Versions/A/Headers \
					-I./frameworks/SDL2_image.framework/Versions/A/Headers \
					-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \

FRAMEWORKS		=	-F./frameworks \
					-rpath ./frameworks \
					-framework OpenGL -framework AppKit -framework OpenCl \
					-framework SDL2 -framework SDL2_ttf -framework SDL2_image

LIBS			=	-L$(FT_DIR) -lft \
					-L$(UI_DIR) -lui \
					-L$(CL_DIR) -lcl \
					-L$(JTOC_DIR) -ljtoc

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo "$(TEXT_CC)$(TEXT_B)↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ all$(TEXT_R)"
	@touch $(TEMP)
	@echo "$(TEXT_CR)$(TEXT_B)LIBFT:$(TEXT_R)"
	@make -C $(FT_DIR) all
	@echo "$(TEXT_CR)$(TEXT_B)LIBCL:$(TEXT_R)"
	@make -C $(CL_DIR) all
	@echo "$(TEXT_CR)$(TEXT_B)LIBJTOC:$(TEXT_R)"
	@make -C $(JTOC_DIR) all
	@echo "$(TEXT_CR)$(TEXT_B)LIBUI:$(TEXT_R)"
	@make -C $(UI_DIR) all
	@echo "$(TEXT_CR)$(TEXT_B)$(NAME):$(TEXT_R)"
	@make $(OBJ_DIR)
	@make compile
	@rm -f $(TEMP)
	@echo "$(TEXT_CG)$(TEXT_BL)$(TEXT_B)↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ success$(TEXT_R)"

compile: $(OBJ)
	@if [ $(CAT_TEMP) ] ; \
		then \
		make build;\
		fi;

build:
	$(CC) $(CFLAGS) $(OBJ) $(INCS) $(LIBS) $(FRAMEWORKS) -o $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<
	@echo "1" > $(TEMP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/interface/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<
	@echo "1" > $(TEMP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/rt_jtoc/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<
	@echo "1" > $(TEMP)

clean:
	@echo "$(TEXT_CC)$(TEXT_B)↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ clean$(TEXT_R)"
	@echo "$(TEXT_CR)$(TEXT_B)LIBFT:$(TEXT_R)"
	@make -C $(FT_DIR) clean
	@echo "$(TEXT_CR)$(TEXT_B)LIBCL:$(TEXT_R)"
	@make -C $(CL_DIR) clean
	@echo "$(TEXT_CR)$(TEXT_B)LIBJTOC:$(TEXT_R)"
	@make -C $(JTOC_DIR) clean
	@echo "$(TEXT_CR)$(TEXT_B)LIBUI:$(TEXT_R)"
	@make -C $(UI_DIR) clean
	@echo "$(TEXT_CR)$(TEXT_B)$(NAME):$(TEXT_R)"
	@rm -f $(TEMP)
	rm -rf $(OBJ_DIR)
	@echo "$(TEXT_CG)$(TEXT_BL)$(TEXT_B)↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ success$(TEXT_R)"

fclean:
	@echo "$(TEXT_CC)$(TEXT_B)↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ fclean$(TEXT_R)"
	@echo "$(TEXT_CR)$(TEXT_B)LIBFT:$(TEXT_R)"
	@make -C $(FT_DIR) fclean
	@echo "$(TEXT_CR)$(TEXT_B)LIBCL:$(TEXT_R)"
	@make -C $(CL_DIR) fclean
	@echo "$(TEXT_CR)$(TEXT_B)LIBJTOC:$(TEXT_R)"
	@make -C $(JTOC_DIR) fclean
	@echo "$(TEXT_CR)$(TEXT_B)LIBUI:$(TEXT_R)"
	@make -C $(UI_DIR) fclean
	@echo "$(TEXT_CR)$(TEXT_B)$(NAME):$(TEXT_R)"
	@rm -f $(TEMP)
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	@echo "$(TEXT_CG)$(TEXT_BL)$(TEXT_B)↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ success$(TEXT_R)"

re: fclean all

# norm:
# 	@echo "$(TEXT_CC)$(TEXT_B)↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ norminette$(TEXT_R)"
# 	@norminette $(SRC_DIR)
# 	@norminette $(INC_DIR)
# 	@norminette $(UI_DIR)/src
# 	@norminette $(UI_DIR)/inc
# 	@echo "$(TEXT_CG)$(TEXT_BL)$(TEXT_B)↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ success$(TEXT_R)"

.PHONY: all $(NAME) clean fclean re norm
