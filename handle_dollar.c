/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:36:45 by merdal            #+#    #+#             */
/*   Updated: 2024/10/18 19:26:46 by mgering          ###   ########.fr       */
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
		if (ft_strcmp(current->var_name, env_variable) == 0)
		{
			new_variable = ft_strdup(current->var_value);
			if (new_variable == NULL)
				return (NULL);
			return (new_variable);
		}
		current = current->next;
	}
	new_variable = NULL;
	return (new_variable);
}

char	*ft_single_dollar(char *new_input)
{
	new_input = malloc(sizeof(char) * 2);
	if (!new_input)
		return (NULL);
	new_input[0] = '$';
	new_input[1] = '\0';
	return (new_input);
}

char	*ft_replace(char *input, int i, t_env *env)
{
	int		len;
	int		j;
	char	*env_variable;
	char	*new_input;

	i++;
	len = i;
	j = -1;
	new_input = NULL;
	if (!input[i] || input[i] == ' ' || input[i] == '\"' || input[i] == '\'')
		return (ft_single_dollar(new_input));
	while (input[len] && input[len]
		!= '\"' && input[len] != '\'' && input[len] != ' ')
		len++;
	env_variable = malloc(sizeof(char) * (len - i) + 1);
	if (!env_variable)
		return (NULL);
	while (++j < len)
	{
		env_variable[j] = input[i];
		i++;
	}
	new_input = ft_search_env_variable(env_variable, env);
	free(env_variable);
	return (new_input);
}

char	*ft_exitstatus(t_env *env)
{
	char	*exit;

	exit = ft_lltoa(env->exit_status);
	return (exit);
}

char	*ft_handle_dollar(char *input, t_env *env)
{
	int		i;
	int		quote;
	char	*new_input;

	i = 0;
	quote = 0;
	new_input = NULL;
	while (input[i])
	{
		if (input[i] == '\"')
			quote = 1;
		if (input[i] == '$' && input[i + 1] == '?')
			new_input = ft_exitstatus(env);
		else if (input[i] == '$' && quote == 0)
			new_input = ft_replace(input, i, env);
		i++;
	}
	return (new_input);
}
