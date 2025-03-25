NAME = miniRT

BIN_DIR = bin
INCLUDES = -Iincludes -Ilibft/includes -Imlx

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP $(INCLUDES) -g3
MLXFLAGS = -lX11 -lXext -lbsd -lm

VPATH = srcs:srcs/parser/

SRCS =	main.c			\
		utils.c			\
		start.c			\
		init.c			\
		parse.c			\
		parse_objects.c	\
		parse_utils.c	\
		print_struct.c	\

OBJS = $(addprefix $(BIN_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

all: $(BIN_DIR) libft mlx $(NAME)

$(BIN_DIR):
		@mkdir -p $(BIN_DIR)

libft:
		@echo "Compiling libft..."
		@$(MAKE) -C libft --no-print-directory > /dev/null 2>&1

mlx:
		@echo "Compiling mlx..."
		@$(MAKE) -C mlx --no-print-directory > /dev/null 2>&1

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) libft/bin/libft.a mlx/libmlx.a -o $(NAME) $(MLXFLAGS)

$(BIN_DIR)/%.o: %.c Makefile | $(BIN_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

norm:
		norminette srcs includes

file = scene1

scene: all
		./$(NAME) scenes/$(file).rt

leaks: all
		valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./$(NAME) scenes/$(file).rt

clean:
		@rm -rf $(BIN_DIR)
		@$(MAKE) -C libft clean --no-print-directory > /dev/null 2>&1
		@$(MAKE) -C mlx clean --no-print-directory > /dev/null 2>&1

fclean:
		@rm -rf $(BIN_DIR)
		@rm -f $(NAME)
		@$(MAKE) -C libft fclean --no-print-directory > /dev/null 2>&1
		@$(MAKE) -C mlx clean --no-print-directory > /dev/null 2>&1
		@rm -f mlx/libmlx.a > /dev/null 2>&1

re: fclean all

.PHONY: all libft mlx leaks clean fclean re

-include $(DEPS)
