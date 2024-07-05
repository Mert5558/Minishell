/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:54:14 by merdal            #+#    #+#             */
/*   Updated: 2024/07/04 15:15:18 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_input(void)
{
	char	*input;

	input = readline(" -- minishell -- $ ");
	return (input);
}

int	ft_check_quotes(char *input)
{
	char 	quote_type;
	int 	i;

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

int	ft_check_input(char *input)
{
	if (input == NULL)
	{
		printf("Error: input is NULL\n");
		return (1);
	}
	if (input[0] == '\0')
	{
		printf("Error: input is empty\n");
		return (1);
	}
	if (ft_check_quotes(input))
	{
		printf("Error: unclosed quotes\n");
		return (1);
	}
	ft_check_syntax(input);
	ft_check_op(input);
	ft_check_syntax_op(input);

	return (0);
}
