/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:52:57 by mgering           #+#    #+#             */
/*   Updated: 2024/10/16 12:55:13 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_varlst(t_varlst *varlst, char *var_name, char *var_value)
{
	while (varlst)
	{
		if (strcmp(varlst->var_name, var_name) == 0)
		{
			free(varlst->var_value);
			varlst->var_value = ft_strdup(var_value);
			return ;
		}
		varlst = varlst->next;
	}
}

void	ft_cd(const t_cmd *cmd, t_env *env)
{
	char		*path;
	char		cwd[PATH_MAX];
	char		*old_pwd;
	t_varlst	*varlst;

	varlst = env->envp_list;
	path = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		old_pwd = ft_strdup(cwd);
	}
	else
	{
		perror("getcwd");
		return ;
	}
	if (cmd->args[1] == NULL)
		check_home_path(varlst, &path);
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		path = getenv("OLDPWD");
		if (path == NULL)
		{
			perror("cd: OLDPWD not set");
			free(old_pwd);
			return ;
		}
		printf("%s\n", path);
	}
	else
		path = cmd->args[1];
	if (0 != access(path, X_OK) || 0 != chdir(path))
	{
		ft_return_and_exit("cd: permission denied", 1, env);
		free(old_pwd);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("OLDPWD", old_pwd, 1);
		ft_update_varlst(varlst, "OLDPWD", old_pwd);
		setenv("PWD", cwd, 1);
		ft_update_varlst(varlst, "PWD", cwd);
	}
	else
		perror("getcwd");
	free(old_pwd);
}

void	check_home_path(t_varlst *varlst, char **path)
{
	while (varlst != NULL)
	{
		if (0 == ft_strcmp(varlst->var_name, "HOME"))
		{
			*path = varlst->var_value;
			break ;
		}
		varlst = varlst->next;
	}
	if (*path == NULL)
	{
		perror("cd: HOME not set");
		return ;
	}
}
