# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 18:00:56 by mjuncker          #+#    #+#              #
#    Updated: 2025/04/25 12:09:22 by mjuncker         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# paths
OBJ_D		= obj/
SRCS_D		= src/
BIN_D		= bin/
INCLUDES_D	= includes/

VPATH = src:src/str:src/mem:src/math:src/link_lst:src/is:src/io:src/vector

# src file names
SRCS =  ft_isalpha.c 		\
		ft_isdigit.c 		\
		ft_isalnum.c 		\
		ft_isascii.c 		\
		ft_isprint.c 		\
		ft_strlen.c 		\
		ft_memset.c 		\
		ft_bzero.c 			\
		ft_memcpy.c			\
		ft_memmove.c 		\
		ft_strlcpy.c 		\
		ft_strlcat.c 		\
		ft_toupper.c 		\
		ft_tolower.c 		\
	    ft_strchr.c 		\
		ft_strrchr.c 		\
		ft_strncmp.c 		\
		ft_memchr.c 		\
		ft_memcmp.c 		\
		ft_strnstr.c 		\
		ft_atoi.c 			\
		ft_calloc.c 		\
		ft_strdup.c 		\
		ft_substr.c 		\
		ft_strjoin.c 		\
		ft_strtrim.c 		\
		ft_split.c 			\
		ft_itoa.c 			\
		ft_strmapi.c 		\
		ft_putchar_fd.c 	\
		ft_putstr_fd.c 		\
		ft_putendl_fd.c 	\
		ft_putnbr_fd.c 		\
		ft_striteri.c		\
		ft_lstadd_front.c 	\
		ft_lstsize.c 		\
		ft_lstlast.c 		\
		ft_lstadd_back.c 	\
		ft_lstdelone.c 		\
		ft_lstclear.c 		\
		ft_lstiter.c 		\
		ft_lstmap.c			\
		ft_get_next_line.c	\
		ft_printf.c			\
		ft_lstchr.c			\
		ft_numbers.c		\
		ft_debug.c			\
		ft_lstnew.c			\
		ft_lstprint.c		\
		ft_iswhitespace.c	\
		ft_atos.c			\
		ft_sortarr.c		\
		ft_dprintf.c		\
		ft_vec_utils1.c		\
		ft_vec_utils2.c		\
		ft_vec_utils3.c		\
		ft_vecnew.c			\
		ft_assertion.c		\
		PCG.c				\
		ft_log.c			\
		ft_assemble.c		\

OBJ = $(SRCS:.c=.o)

# adding path for src and obj
OBJ := $(addprefix $(OBJ_D), $(OBJ))
SRCS := $(addprefix $(SRCS_D), $(SRCS))
DEPS = $(OBJ:.o=.d)

# compiler settings
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES_D) -D BUFFER_SIZE=20 -MP -MMD -g3
MAKEFLAGS += -s

# commands
RM = rm -fr

RESET 		= \033[0m
GRAY		=\033[90m
RED 		= \033[31m
GREEN 		= \033[32m
YELLOW 		= \033[33m
BLUE 		= \033[34m
CURSOR_OFF 	= \e[?25l
CURSOR_ON 	= \e[?25h


.PHONY: all
all : $(BIN_D)$(NAME)

$(BIN_D)$(NAME): $(OBJ) | $(BIN_D)
	ar rcs $(BIN_D)$(NAME) $(OBJ)
	printf "$(GREEN)$(NAME): success\n"
	printf "\n---------------------$(CURSOR_ON)\n\n"

$(OBJ_D)%.o: %.c includes/libft.h Makefile | $(OBJ_D)
	printf "$(CURSOR_OFF)$(BLUE)"
	$(CC) $(CFLAGS) -c $< -o $@
	printf "$(GRAY)compiling: $(BLUE)%-40s $(GRAY)[%d/%d]\n" "$<" "$$(find ./obj/ -maxdepth 1 -type f -name '*.o' | wc -l)" "$(words $(SRCS))"


$(OBJ_D):
	mkdir -p $(OBJ_D)

$(BIN_D):
	mkdir -p $(BIN_D)

.PHONY: clean
clean:
	printf "\n$(RED)clean:\t$(NAME)\n\n$(RESET)"
	$(RM) $(OBJ_D)


.PHONY: fclean
fclean:
	printf "\n$(RED)fclean:\t$(NAME)$(RESET)"
	$(MAKE) clean
	$(RM) $(BIN_D)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

debug: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN_D)a.out
	echo "$(GREEN)[SUCCESS]$(RESET)"

run: debug
	$(BIN_D)a.out

-include $(DEPS)
