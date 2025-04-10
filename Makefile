NAME = miniRT

OBJ_DIR = obj
INCLUDES = -Iincludes -Ilibft/includes -Imlx

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP $(INCLUDES) -g3
MLXFLAGS = -lX11 -lXext -lbsd -lm

VPATH = srcs:srcs/parser:srcs/renderer:srcs/camera

SRCS =	main.c			\
		utils.c			\
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
		button.c		\
		sphere.c		\
		plane.c			\
		cylinder.c		\
		lighting.c		\
		pipeline.c		\
		camera.c		\
		phong_model.c	\

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
		valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) scenes/$(file).rt

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

