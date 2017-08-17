# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/07 18:50:11 by mbriffau          #+#    #+#              #
#    Updated: 2017/08/01 15:54:49 by mbriffau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libft.a

CC =			gcc

FLAGS =			-Wall -Werror -Wextra

HEADER =		libft.h

HEADER_DIR =	./

FT_SRC_DIR =	./$(SRCS)

SRCS = 			srcs/

FT_FILES =		ft_putchar \
				ft_putstr \
				ft_strlen \
				ft_strcat \
				ft_strncat \
				ft_strlcat \
				ft_strcpy \
				ft_strncpy \
				ft_strdup \
				ft_strndup \
				ft_strcmp \
				ft_strncmp \
				ft_strstr \
				ft_strnstr \
				ft_strchr \
				ft_strrchr \
				ft_isalpha \
				ft_isdigit \
				ft_isalnum \
				ft_isprint \
				ft_isascii \
				ft_tolower \
				ft_toupper \
				ft_bzero \
				ft_memset \
				ft_memchr \
				ft_memcmp \
				ft_memcpy \
				ft_memccpy \
				ft_memmove \
				ft_atoi \
				ft_memalloc \
				ft_memdel \
				ft_strnew \
				ft_strdel \
				ft_strclr \
				ft_striter \
				ft_striteri \
				ft_strmap \
				ft_strmapi \
				ft_strequ \
				ft_strnequ \
				ft_strsub \
				ft_strjoin \
				ft_strtrim \
				ft_strsplit \
				ft_itoa \
				ft_putendl \
				ft_putnbr \
				ft_putchar_fd \
				ft_putstr_fd \
				ft_putendl_fd \
				ft_putnbr_fd \
				ft_lstnew \
				ft_lstdelone \
				ft_lstdel \
				ft_lstadd \
				ft_lstiter \
				ft_lstmap \
				ft_swap \
				ft_iterative_factorial \
				ft_strrev \
				ft_count_word \
				ft_wordlen \
				ft_double_memalloc \
				ft_strlen_c \
				ft_strcut \
				ft_strnjoinfree \
				ft_itoa_base \
				ft_error

FT_COMPILED =	$(addsuffix .o,$(FT_FILES))

COMPILED =		$(FT_COMPILED)

all: $(NAME)

$(NAME): $(FT_COMPILED)
	ar rc $(NAME) $(FT_COMPILED)
	ranlib $(NAME)

$(FT_COMPILED): %.o: $(FT_SRC_DIR)%.c $(HEADER)
	$(CC) -c $(FLAGS) -I $(HEADER_DIR) $< -o $@

clean:
	-/bin/rm -f $(COMPILED)

fclean: clean
	-/bin/rm -f $(NAME)

re: fclean all
