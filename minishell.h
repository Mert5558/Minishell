/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:07:42 by merdal            #+#    #+#             */
/*   Updated: 2024/06/30 13:18:41 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	TOKEN_CMD,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_OPERATOR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
}t_token_type;


typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		input_fd;
	int		output_fd;
}t_cmd;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
}t_env;


char	*ft_get_input(void);
int		ft_check_input(char *input);



#endif