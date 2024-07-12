/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:36:45 by merdal            #+#    #+#             */
/*   Updated: 2024/07/12 14:40:10 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_search_env_variable(char *env_variable, t_env *env)
{
	char		*new_variable;
	t_varlst	*current;

	current = env->envp_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->var_name, env_variable, ft_strlen(env_variable)) == 0)
		{
			new_variable = ft_strdup(current->var_value);
			if (new_variable == NULL)
				return (NULL);
			return (new_variable);
		}
		current = current->next;
	}
	return (NULL);
}

char	*ft_replace(char *input, int i, t_env *env)
{
	int	len;
	int	j;
	char	*env_variable;
	char	*new_input;

	i++;
	len = i;
	j = 0;
	if (!input[i] || input[i] == ' ' || input[i] == '\"' || input[i] == '\'')
	{
		printf("$");
		//return (1);
	}
	while (input[len] && input[len] != '\"' && input[len] != '\'' && input[len] != ' ')
		len++;
	env_variable = malloc(sizeof(char) * (len - i) + 1);
	if (!env_variable)
		return (0);
	while (j < len - i)
	{
		env_variable[j] = input[i];
		i++;
		j++;
	}
	new_input = ft_search_env_variable(env_variable, env);
	return (new_input);
}

void	ft_exitstatus(t_env *env)
{
	printf("%lld\n", env->exit_status);
	env->exit_status = 0;
}

char	*ft_handle_dollar(char *input, t_env *env)
{
	int		i;
	int 	quote;			//quote bool in struct;
	char	*new_input;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote = 1;
		if (input[i] == '$' && input[i + 1] == '?')
			ft_exitstatus(env);
		else if (input[i] == '$' && quote == 0)
			new_input = ft_replace(input, i, env);
		i++;
	}
	return (new_input);
}
