/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:23:00 by mgering           #+#    #+#             */
/*   Updated: 2024/09/20 12:56:06 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options */

void	ft_clear(void);

void	*ft_check_args(const t_cmd *cmd, t_env *env)
{
	char	**arg;

	arg = cmd->args;
	if (0 == ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (0 == ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd);
	else if (0 == ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd();
	else if (0 == ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd, env);
	else if (0 == ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd, env);
	else if (0 == ft_strcmp(cmd->args[0], "env"))
		ft_env(env);
	else if (0 == ft_strcmp(cmd->args[0], "clear"))
		ft_clear();
	// else if (arg[0] == "exit")
	// 	//ft_exit(cmd);
	else
		ft_exe(cmd, env);
	return(NULL);
}


void	ft_clear(void)
{
	printf("\033[2J\033[H");
}
