/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:56:22 by merdal            #+#    #+#             */
/*   Updated: 2024/10/13 16:00:23 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_return_and_exit(char *error, int exit_status, t_env *env)
{
	if (error == NULL)
		return ;
	else
		printf("%s\n", error);
	env->exec_flag = 1;
	env->exit_status = exit_status;
}

int	ft_skip_quotes(char *input, int *i)
{
	char	quotes;

	quotes = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quotes)
		(*i)++;
	if (input[*i] == quotes)
		(*i)++;
	return (1);
}

int	ft_token_len(char *input, int i)
{
	size_t	len;

	len = 0;
	if (input[i] == '|' || input[i] == '&' || input[i] == ';'
		|| input[i] == '>' || input[i] == '<')
	{
		if (input[i] == '>' && input[i + 1] == '>')
			return (2);
		if (input[i] == '<' && input[i + 1] == '<')
			return (2);
		return (1);
	}
	while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '&'
		&& input[i] != ';' && input[i] != '>' && input[i] != '<')
	{
		if (input[i] == '\"' || input[i] == '\'')
			ft_skip_quotes(input, &i);
		else
			i++;
		len++;
	}
	return (len);
}
