#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nflores <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/08 15:23:08 by nflores           #+#    #+#              #
#    Updated: 2016/02/16 11:16:53 by nflores          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

SRC = ft_flag.c ft_itoa.c ft_itoa_base.c ft_printf.c ft_printf_d.c ft_putstr.c \
	ft_strcat.c ft_strcpy.c ft_strdup.c ft_strlen.c ft_strnew.c ft_putchar.c \
	lowercase.c ft_printf_c.c ft_printf_s.c ft_printf_p.c ft_printf_o.c \
	ft_printf_x.c ft_printf_u.c ft_printf_mo.c ft_printf_md.c ft_printf_mu.c \
	ft_printf_pct.c ft_atoi.c ft_strsub.c ft_atoi_bin.c ft_modif.c ft_setmodif.c \
	ft_setwidth.c ft_setwidth_o.c ft_printf_ms.c ft_isdigit.c ft_isalpha.c \
	ft_strcmp.c ft_print_oct.c ft_prec_d.c ft_putwchar.c ft_setwidth_p.c \
	ft_setwidth_s.c ft_printf_mx.c ft_setwidth_d.c ft_setoct_s.c ft_memcmp.c \
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	ft_strncpy.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_isalnum.c ft_memdel.c ft_strdel.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c \
	ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
	ft_strnequ.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_putchar.c ft_putstr.c \
	ft_putnbr.c ft_putendl.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c 	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	ft_lstmap.c ft_lstaddend.c ft_min.c ft_max.c ft_mintab.c ft_maxtab.c

OBJ = $(SRC:.c=.o)

HEAD = libft.h ft_printf.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -I $(HEAD) -c $(SRC)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ) ft_printf.h.gch

fclean: clean
	@rm -f $(NAME)

re: fclean all
