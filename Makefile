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
SRCS =	main.c						\
		utils.c						\
		free.c						\
		init.c						\
		parse.c						\
		parse_objects.c				\
		parse_utils.c					\
		print_struct.c				\
		print_struct_utils.c			\
		parse_material.c				\
		image.c						\
		window.c						\
		renderer.c					\
		ray.c							\
		colors.c						\
		sphere.c						\
		plane.c						\
		cylinder.c					\
		cone.c						\
		lighting.c					\
		pipeline.c					\
		camera.c						\
		cam_transform.c				\
		phong_model.c					\
		intersection.c				\
		input.c						\
		input_utils.c					\
		checker.c						\
		ppm_loader.c					\
		ppm_header.c					\
		ppm_utils.c					\
		effects_complex.c				\
		effects_simple.c				\
		ppm_saver.c					\
		button.c						\
		draw_objects_controls.c		\
		put_string_win.c				\
		put_string_objects.c			\
		put_string_objects_utils.c	\
		put_mat_info.c				\
		handle_button_click.c			\
		handle_button_click_utils.c	\
		handle_mouse_move.c			\
		handle_mouse_move_utils.c		\
		handle_dragging_slider.c		\
		draw.c						\
		draw_utils.c					\
		init_button.c					\
		init_button_utils.c			\
		handle_tabs.c					\
		uv.c							\
		hit.c							\
		depth_of_field.c				\
		renderer_utils.c				\
		antialiaser.c					\

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

file = scene1

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
