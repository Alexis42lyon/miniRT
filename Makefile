NAME = miniRT

OBJ_DIR = obj
INCLUDES = -Iincludes -Ilibft/includes -Imlx

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP $(INCLUDES) -g3
MLXFLAGS = -lX11 -lXext -lbsd -lm

VPATH = srcs:srcs/parser:srcs/renderer:srcs/camera:srcs/textures

SRCS =	main.c					\
		utils.c					\
		free.c					\
		init.c					\
		parse.c					\
		parse_objects.c			\
		parse_utils.c			\
		print_struct.c			\
		print_struct_utils.c	\
		parse_material.c		\
		image.c					\
		window.c				\
		renderer.c				\
		ray.c					\
		colors.c				\
		button.c				\
		sphere.c				\
		plane.c					\
		cylinder.c				\
		cone.c					\
		lighting.c				\
		pipeline.c				\
		camera.c				\
		cam_transform.c			\
		phong_model.c			\
		intersection.c			\
		anti_aliasing.c			\
		denoising.c				\
		input.c					\
		checker.c				\
		ppm_loader.c			\
		ppm_header.c			\
		ppm_utils.c				\

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)


RESET 			= \033[0m
GRAY			= \033[90m
RED 			= \033[31m
GREEN 			= \033[32m
YELLOW 			= \033[33m
BLUE 			= \033[34m

all: $(OBJ_DIR) libft mlx $(NAME)
	printf "$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

libft:
	@echo "Compiling libft..."
	@$(MAKE) -C libft

mlx:
	@echo "Compiling mlx..."
	@$(MAKE) -C mlx > /dev/null 2>&1

$(NAME): $(OBJS) libft mlx Makefile
	$(CC) $(CFLAGS) $(OBJS) libft/bin/libft.a mlx/libmlx.a -o $(NAME) $(MLXFLAGS)

$(OBJ_DIR)/%.o: %.c Makefile | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	printf "$(GRAY)compiling: $(BLUE)%-40s $(GRAY)[%d/%d]\n" "$<" "$$(ls obj | wc -l)" "$(words $(SRCS))"

norm:
		norminette srcs includes

file = scene1

scene: all
		./$(NAME) scenes/$(file).rt

leaks: all
		valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=all ./$(NAME) scenes/$(file).rt

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean > /dev/null 2>&1
	$(MAKE) -C mlx clean > /dev/null 2>&1

fclean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)
	$(MAKE) -C libft fclean > /dev/null 2>&1
	$(MAKE) -C mlx clean > /dev/null 2>&1
	rm -f mlx/libmlx.a > /dev/null 2>&1

re: fclean all

.PHONY: all libft mlx leaks clean fclean re

-include $(DEPS)
.SILENT:

