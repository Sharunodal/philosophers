# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 09:09:59 by arissane          #+#    #+#              #
#    Updated: 2024/11/08 11:53:01 by arissane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

SRCS = main.c \
       init.c \
       actions.c \
       utils.c \
       time.c \
       observer.c \

OFILES = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
	@echo "program compiled"

clean:
	@rm -f $(OFILES)
	@echo "removed object files"

fclean: clean
	@rm -f $(NAME)
	@echo "removed executable"

re: fclean all

.PHONY: all clean fclean re
