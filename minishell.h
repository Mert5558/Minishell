/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:07:42 by merdal            #+#    #+#             */
/*   Updated: 2024/09/20 15:20:07 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
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
	char	*operator;
	char	**args;
	int		input_fd;
	int		output_fd;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}t_token;

typedef struct s_varlst
{
	char *var_name;
	char *var_value;
	struct s_varlst *next;
}t_varlst;

typedef struct s_env
{
	char		**envp;
	t_varlst 	*envp_list;
	char		*key;
	char		*value;
	long long	exit_status;
}t_env;


char	*ft_get_input(void);
int		ft_check_input(char *input, t_env *env);
int		ft_check_syntax(char *input, t_env *env);
int		ft_check_op(char *input, t_env *env);
int		ft_check_syntax_op(char *input, t_env *env);
char	*ft_handle_dollar(char *input, t_env *env);
void	ft_init(char **envp, t_env *env);
void	ft_return_and_exit(char *error, int exit_status, t_env *env);
int		ft_count_tokens(char *input);
char	**ft_create_array(char *input, t_env *env);
int		ft_count_tokens(char *input);
int		ft_token_len(char *input, int i);
t_cmd	*ft_parser(char *input, t_env *env);
t_cmd	*ft_set_fds(t_cmd *temp);

#endif