# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgering <mgering@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 12:50:20 by merdal            #+#    #+#              #
#    Updated: 2024/10/18 20:27:39 by mgering          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -ILibft/src
LDFLAGS = -LLibft -lft -lreadline
NAME = 	minishell

SRCS =	src/minishell.c src/input.c src/input2.c src/handle_dollar.c \
		src/ft_init.c src/utils.c src/tokenize.c src/parser.c src/ft_check_args.c \
		src/build_in_cmd/ft_echo.c src/build_in_cmd/ft_cd.c \
		src/build_in_cmd/ft_pwd.c src/build_in_cmd/ft_exe.c src/build_in_cmd/ft_export.c src/build_in_cmd/ft_env.c src/build_in_cmd/ft_exit.c \
		src/build_in_cmd/ft_unset.c src/build_in_cmd/ft_clear.c src/set_fds.c src/utils2.c src/utils3.c src/utils4.c \
		src/signal_handler.c src/free_memory.c src/ft_child_process.c src/ft_pipe_execution.c


OBJS = $(SRCS:.c=.o)
RM = rm -f
LIBFT = Libft/libft.a

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C Libft > /dev/null
	@echo "\033[0;32mlibft compiled\033[0m"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) > /dev/null
	@echo "\033[0;32mminishell compiled\033[0m"

clean:
	@$(RM) $(OBJS)
	@make -C Libft clean > /dev/null
	@echo "\033[0;32mObject files removed\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@make -C Libft fclean > /dev/null
	@echo "\033[0;32mCleaned\033[0m"

re: fclean 
	@echo "---------------------"
	@$(MAKE) all

.PHONY: all clean fclean re