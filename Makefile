# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/13 11:43:23 by jrameau           #+#    #+#              #
#    Updated: 2016/12/24 15:41:33 by jrameau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = 	$(shell ls | grep -E ".+\.c")

LIBDIR = ./libft/
INC = .
LIBFT = ./libft/libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra

all: $(SRCS) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(SRCS) -I$(INC) -I./libft/includes $(LIBFT) -g

$(LIBFT):
	make -C $(LIBDIR)

clean:
	/bin/rm -rf $(NAME)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
