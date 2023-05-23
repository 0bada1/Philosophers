# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 14:03:45 by ooutabac          #+#    #+#              #
#    Updated: 2023/05/23 14:18:40 by ooutabac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = 	philosophers.c		\
			check_errors.c		\
			free.c				\
			libft.c				\
			utils.c				\
			utils2.c			\
			utils3.c			\
			parsing.c			\
			main.c				\

OBJ = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(SOURCES) -c $< -o $@

$(NAME):
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: clean fclean all

.PHONY: all clean fclean re
