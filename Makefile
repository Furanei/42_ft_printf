# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/29 22:02:18 by mbriffau          #+#    #+#              #
#    Updated: 2017/08/14 23:34:09 by mbriffau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf

CC = gcc

FLAGS = -Wall -Wextra -Werror

INC = libft/libft.a

SRCS = srcs/

DIR = ./

FILES = 		ft_printf.c \
				parse_conversion.c \
				conv_c.c \
				conv_s.c \
				conv_d.c \
				conv_p.c \
				conv_x.c \
				conv_o.c \
				option.c \
				conv_u.c \
				conv_b.c \
				init_conv.c \
				call_buffer.c \

all : $(NAME)

$(NAME):
	@gcc -o $(NAME) $(DIR)$(FILES) main.c $(INC)
	@gcc -o true_printf test_printf.c

clean :
	rm ft_printf
	rm true_printf

fclean : clean

make re: fclean all
