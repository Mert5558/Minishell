# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: merdal <merdal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 12:50:20 by merdal            #+#    #+#              #
#    Updated: 2024/07/02 12:14:46 by merdal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -Llibft -lft -lreadline
NAME = 	minishell

SRCS =	minishell.c \
		input.c \
		input2.c

OBJS = $(SRCS:.c=.o)
RM = rm -f
LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft > /dev/null
	@echo "\033[0;32mlibft compiled\033[0m"

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	@make -C libft clean

fclean: clean
	$(RM) $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re