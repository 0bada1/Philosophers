# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 06:03:21 by ooutabac          #+#    #+#              #
#    Updated: 2023/01/26 21:16:24 by ooutabac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = 	philo.c				\
			parsing.c			\
			free.c				\
			
OBJ = (SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SOURCES)

clean: $(OBJ)
	rm -rf $(OBJ)
	
fclean: clean $(NAME)
	rm -rf $(NAME)
	
re: clean fclean all

.PHONY: all clean fclean re
