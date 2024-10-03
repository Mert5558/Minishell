/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:54:14 by merdal            #+#    #+#             */
/*   Updated: 2024/10/02 13:57:34 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_input()
{
	char	*input;

	input = readline(" -- minishell -- $ ");
	if (g_signal_received == SIGINT)
	{
		//free_cmd(cmd);
		return (NULL);
	}
	if (input == NULL || ft_strcmp(input, "exit") == 0)
	{
		printf("exit");
		exit (0);
	}
	return (input);
}

int	ft_check_quotes(char *input)
{
	char	quote_type;
	int		i;

	quote_type = 0;
	i = 0;
	while (input[i] && !quote_type)
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote_type = input[i];
		i++;
	}
	while (input[i] && quote_type)
	{
		if (input[i] && input[i] == quote_type)
			quote_type = 0;
		i++;
	}
	if (input[i])
		return (ft_check_quotes(&input[i]));
	else if (!quote_type)
		return (0);
	else
		return (1);
}

int	ft_check_input(char *input, t_env *env)
{
	if (input == NULL)
	{
		ft_return_and_exit("Error: input is NULL", 1, env);
		return (1);
	}
	if (input[0] == '\0')
	{
		ft_return_and_exit(NULL, 2, env);
		return (1);
	}
	if (ft_check_quotes(input))
	{
		ft_return_and_exit("Error: unclosed quotes", 2, env);
		return (1);
	}
	ft_check_syntax(input, env);
	ft_check_op(input, env);
	ft_check_syntax_op(input, env);
	return (0);
}
