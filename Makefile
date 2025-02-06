# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/27 15:27:49 by sfrankie          #+#    #+#              #
#    Updated: 2024/02/14 19:21:56 by sfrankie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = philo

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRC = src/main.c src/error.c src/philo_cycle.c src/philo_cycle_2.c \
	src/philo_setup.c src/main_utils.c src/philo_cycle_utils.c \
	src/philo_cycle_utils_2.c src/philo_cycle_utils_3.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -pthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all