/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:23:00 by mgering           #+#    #+#             */
/*   Updated: 2024/10/14 15:59:16 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_check_args(const t_cmd *cmd, t_env *env)
{
	const t_cmd	*tmp_cmd;

	tmp_cmd = cmd;
	if (tmp_cmd == NULL)
	{
		env->exit_status = g_signal_received;
		return (NULL);
	}
	if (tmp_cmd->args == NULL)
		return (NULL);
	if (env->exec_flag == 1)
		return (NULL);
	while (tmp_cmd)
	{
		if (0 == ft_strcmp(tmp_cmd->args[0], "cd")
			|| 0 == ft_strcmp(tmp_cmd->args[0], "export")
			|| 0 == ft_strcmp(tmp_cmd->args[0], "unset")
			|| 0 == ft_strcmp(tmp_cmd->args[0], "exit"))
			execute_parent(tmp_cmd, env);
		else
			execute_child(tmp_cmd, env);
		tmp_cmd = tmp_cmd->next;
	}
	return (NULL);
}

void	execute_parent(const t_cmd *cmd, t_env *env)
{
	redirect_fd(cmd);
	if (0 == ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, env);
	else if (0 == ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd, env);
	else if (0 == ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd, env);
}

void	execute_child(const t_cmd *cmd, t_env *env)
{
	int	pid ;

	pid = fork();
	if (pid == 0)
		child_process(cmd, env);
	else if (pid > 0)
		wait_child_process(cmd, env, pid);
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	redirect_fd(const t_cmd *cmd)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) < 0)
		{
			perror("dup2 input_fd");
			exit(EXIT_FAILURE);
		}
		close(cmd->input_fd);
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 output_fd");
			exit(EXIT_FAILURE);
		}
		close(cmd->output_fd);
	}
}

void	check_executable(const t_cmd *cmd, t_env *env)
{
	if (0 == ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (0 == ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd();
	else if (0 == ft_strcmp(cmd->args[0], "env"))
		ft_env(env);
	else if (0 == ft_strcmp(cmd->args[0], "clear"))
		ft_clear();
	else
		ft_exe(cmd, env);
}
