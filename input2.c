/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:54:54 by merdal            #+#    #+#             */
/*   Updated: 2024/07/03 15:10:35 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_syntax(char *input)
{
	if (input[0] == '|' || input[ft_strlen(input) - 1] == '|')
	{
		printf("Error: syntax error pipes\n");
		return (1);
	}
	if (input[ft_strlen(input) - 1] == '>')
	{
		printf("Error: syntax error redirection\n");
		return (1);
	}
	if (input[ft_strlen(input) - 1] == '<')
	{
		printf("Error: syntax error redirection\n");
		return (1);
	}
	if (input[ft_strlen(input) - 1] == '>' && input[ft_strlen(input) - 2] == '>')
	{
		printf("Error: syntax error redirection\n");
		return (1);
	}
	return (0);
}

int	ft_check_op(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote = 1;
		if (((input[i] == '>' && input[i + 1] == '<')
				|| (input[i] == '>' && input[i + 1] == '<')
				|| (input[i] == '|' && input[i + 1] == '|')) && quote == 0)
		{
			printf("Error: syntax error\n");
			return (1);
		}
		else if ((input[i] == '{' || input[i] =='}' || input[i] == '[' || input[i] == ']'
					|| input[i] == '(' || input[i] == ')' || input[i] == '&'
					|| input[i] == ';' || input[i] == '*') && quote == 0)
		{
			printf("Error: syntax error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_syntax_op(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while(input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quote = 1;
		if ((input[i] == '<' || input[i] == '>' || input[i] == '|') && quote == 0)
		{
			if (input[i] == input[i + 1])
				i = i + 2;
			else
				i++;
			if (input[i] == ' ')
			{
				while (input[i] == ' ')
					i++;
				if (input[i] == '<' || input[i] == '>' || input[i] == '|')
				{
					printf("Error: syntax error bbbbbbbbbb\n");
					return (1);
				}
			}
			if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			{
				printf("Error: syntax error aaaaaaaaaaa\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
