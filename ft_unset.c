/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:46:48 by mgering           #+#    #+#             */
/*   Updated: 2024/10/15 15:15:47 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(const t_cmd *cmd, t_env *env)
{
	t_varlst	**current;
	t_varlst	*temp;

	if (cmd->args[1] == NULL)
		return ;
	current = &env->envp_list;
	while (*current)
	{
		if (ft_strcmp(cmd->args[1], (*current)->var_name) == 0)
		{
			temp = *current;
			*current = (*current)->next;
			free(temp->var_name);
			free(temp->var_value);
			free(temp);
			return ;
		}
		else
			current = &(*current)->next;
	}
}
