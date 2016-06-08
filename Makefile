#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nflores <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/09 14:19:39 by nflores           #+#    #+#              #
#    Updated: 2016/03/23 16:53:33 by nflores          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRC_PATH = src

SRC_NAME = check_arg.c ft_champ_lstnew.c ft_codage.c ft_function_1_4.c ft_function_5_8.c \
	ft_function_9_12.c ft_function_13_16.c ft_game.c ft_newchamp.c ft_newmem.c \
	ft_param.c ft_print_contest.c ft_print_mem.c ft_proc_lstnew.c ft_proc.c get_opt.c \
	init_champ.c init_vm.c is_opcode.c main.c set_param.c write_value.c ft_index.c \
	exec_opc.c

OBJ_PATH = obj

LDFLAGS = -Llibftprintf

LDLIBS = -lftprintf

NAME = corewar

FLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libftprintf/ fclean && make -C libftprintf/
	gcc $(FLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc $(FLAGS)  -o $@ -c $<

clean:
	make -C libftprintf/ clean
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	make -C libftprintf/ fclean
	rm -f $(NAME)

re: fclean all
