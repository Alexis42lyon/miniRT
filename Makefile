NAME = miniRT
MODE ?= release

OBJ_DIR = obj-$(MODE)
INCLUDES = -Iincludes -Ilibft/includes -Imlx
LIBS = libft/bin/libft.a mlx/libmlx.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP $(INCLUDES)
MLXFLAGS = -lX11 -lXext -lbsd -lm

ifeq ($(MODE), debug)
	CFLAGS += -g3 -D DEFAULT_BOUNCE=1
endif

VPATH = srcs:srcs/parser:srcs/renderer:srcs/camera:srcs/textures:srcs/button

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
		effects.c				\
		ppm_saver.c				\
		button.c				\
		put_string_win.c		\
		slider.c				\
		tabs.c					\
		uv.c					\

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)
BIN = $(NAME)

RESET			= \033[0m
GRAY			= \033[90m
RED 			= \033[31m
GREEN 			= \033[32m
YELLOW 			= \033[33m
BLUE 			= \033[34m

all:
	$(MAKE) libft
	$(MAKE) mlx
	$(MAKE) $(BIN)
	printf "$(RESET)"

debug:
	$(MAKE) MODE=debug

release:
	$(MAKE) MODE=release

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libft:
	$(MAKE) -C libft

mlx:
	$(MAKE) -C mlx > /dev/null 2>&1

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ $(MLXFLAGS)

$(OBJ_DIR)/%.o: %.c Makefile $(LIBS)| $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(GRAY)compiling: $(BLUE)%-40s $(GRAY)[%d/%d]\n" "$<" "$$(ls $(OBJ_DIR) | grep -c '\.o')" "$(words $(SRCS))"

norm:
	norminette srcs includes

file = scene1

scene: all
	./$(BIN) scenes/$(file).rt

leaks: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=all ./$(BIN) scenes/$(file).rt

callgrind: all
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes ./$(BIN) scenes/$(file).rt

clean:
	rm -rf obj-debug obj-release
	$(MAKE) -C libft clean
	$(MAKE) -C mlx clean > /dev/null 2>&1

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C mlx clean > /dev/null 2>&1
	rm -f mlx/libmlx.a

re: fclean all

.PHONY: all libft mlx leaks clean fclean re debug release

-include $(DEPS)
.SILENT:
MAKEFLAGS=--no-print-directory
