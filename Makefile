# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/29 22:02:18 by mbriffau          #+#    #+#              #
#    Updated: 2017/08/22 16:40:24 by mbriffau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf

CC = gcc

LIBFT = libft

FLAGS = -Wall -Wextra -Werror -02

LIB_NAME = $(LIBFT).a

INC = $(LIBFT)/$(LIB_NAME)

SRCS = srcs/$(FILES)

DIR_SRCS = ./$(SRCS)

FILES = 	srcs/ft_printf.c \
				srcs/parse_conversion.c \
				srcs/conv_c.c \
				srcs/conv_s.c \
				srcs/conv_d.c \
				srcs/conv_p.c \
				srcs/conv_x.c \
				srcs/conv_o.c \
				srcs/option.c \
				srcs/conv_u.c \
				srcs/conv_b.c \
				srcs/init_conv.c \
				srcs/call_buffer.c \
				srcs/main.c

all : $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@gcc -o $(NAME) $(FILES) $(INC)
	@echo "ft_printf \033[0;32mcompiled.\033[0m"

clean :
	@rm ft_printf
	@echo "ft_printf \033[1;31mdeleted.\033[0m"

fclean : clean

lib_re : 
	make fclean -C $(LIBFT)

re : lib_re fclean all
