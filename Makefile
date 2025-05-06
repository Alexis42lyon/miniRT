NAME = miniRT
NAME_BONUS = miniRT

MODE ?= release

OBJ_DIR = obj-$(MODE)
LIBS = libft/bin/libft.a mlx/libmlx.a

CC = cc
MLXFLAGS = -lX11 -lXext -lbsd -lm

ifeq ($(MODE),bonus)
VPATH = :srcs_bonus:srcs_bonus/parser:srcs_bonus/renderer:srcs_bonus/camera:srcs_bonus/textures:srcs_bonus/button
CFLAGS = -Wall -Werror -Wextra -MD -MP -Ilibft/includes -Iincludes_bonus -Imlx
SRCS =	main_bonus.c						\
		utils_bonus.c						\
		free_bonus.c						\
		init_bonus.c						\
		parse_bonus.c						\
		parse_objects_bonus.c				\
		parse_utils_bonus.c					\
		print_struct_bonus.c				\
		print_struct_utils_bonus.c			\
		parse_material_bonus.c				\
		image_bonus.c						\
		window_bonus.c						\
		renderer_bonus.c					\
		ray_bonus.c							\
		colors_bonus.c						\
		sphere_bonus.c						\
		plane_bonus.c						\
		cylinder_bonus.c					\
		cone_bonus.c						\
		lighting_bonus.c					\
		pipeline_bonus.c					\
		camera_bonus.c						\
		cam_transform_bonus.c				\
		phong_model_bonus.c					\
		intersection_bonus.c				\
		input_bonus.c						\
		input_utils_bonus.c					\
		checker_bonus.c						\
		ppm_loader_bonus.c					\
		ppm_header_bonus.c					\
		ppm_utils_bonus.c					\
		effects_complex_bonus.c				\
		effects_simple_bonus.c				\
		ppm_saver_bonus.c					\
		button_bonus.c						\
		draw_objects_controls_bonus.c		\
		put_string_win_bonus.c				\
		put_string_objects_bonus.c			\
		put_string_objects_utils_bonus.c	\
		put_mat_info_bonus.c				\
		handle_button_click_bonus.c			\
		handle_button_click_utils_bonus.c	\
		handle_mouse_move_bonus.c			\
		handle_mouse_move_utils_bonus.c		\
		handle_dragging_slider_bonus.c		\
		draw_bonus.c						\
		draw_utils_bonus.c					\
		init_button_bonus.c					\
		init_button_utils_bonus.c			\
		handle_tabs_bonus.c					\
		uv_bonus.c							\
		hit_bonus.c							\
		depth_of_field_bonus.c				\
		renderer_utils_bonus.c				\
		antialiaser_bonus.c					\

file = bonus/scene1

else
VPATH = srcs:srcs/parser:srcs/renderer:srcs/camera
CFLAGS = -Wall -Werror -Wextra -MD -MP -Ilibft/includes -Iincludes -Imlx
SRCS =	main.c			\
		utils.c			\
		free.c			\
		init.c			\
		parse.c			\
		parse_objects.c	\
		parse_utils.c	\
		print_struct.c	\
		image.c			\
		window.c		\
		renderer.c		\
		ray.c			\
		colors.c		\
		sphere.c		\
		plane.c			\
		cylinder.c		\
		lighting.c		\
		pipeline.c		\
		camera.c		\
		cam_transform.c	\
		phong_model.c	\
		intersection.c	\

file = mandatory/scene1

endif

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

RESET 			= \033[0m
GRAY			= \033[90m
RED 			= \033[31m
GREEN 			= \033[32m
YELLOW 			= \033[33m
BLUE 			= \033[34m

all:
	$(MAKE) libft
	$(MAKE) mlx
	$(MAKE) $(NAME)
	printf "$(RESET)"

bonus:
	$(MAKE) MODE=bonus

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libft:
	$(MAKE) -C libft

mlx:
	$(MAKE) -C mlx > /dev/null 2>&1

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ $(MLXFLAGS)

$(OBJ_DIR)/%.o: %.c Makefile $(LIBS)| $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(GRAY)compiling: $(BLUE)%-40s $(GRAY)[%d/%d]\n" "$<" "$$(ls $(OBJ_DIR) | grep -c '\.o')" "$(words $(SRCS))"
norm:
	norminette srcs includes srcs includes libft

scene: all
		./$(NAME) scenes/$(file).rt

leaks: all
		valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) scenes/$(file).rt

clean:
	rm -rf obj-debug obj-release
	$(MAKE) -C libft clean
	$(MAKE) -C mlx clean > /dev/null 2>&1

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	rm -f mlx/libmlx.a

re: fclean all

.PHONY: all libft mlx leaks clean fclean re

-include $(DEPS) $(DEPS_BONUS)

.SILENT:
MAKEFLAGS=--no-print-directory
