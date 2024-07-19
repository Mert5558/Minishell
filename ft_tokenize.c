/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:35:03 by merdal            #+#    #+#             */
/*   Updated: 2024/07/19 15:43:18 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int ft_count_tokens(char *input)
{
    int count = 0;
    int flag = 0;
    int quotes = 0;

    while (*input)
    {
        if (*input == '|' || *input == '&' || *input == ';' || *input == '<')
            count += !quotes;
        else if (*input == '>')
        {
            if (*(input + 1) == '>')
                input++;
            count += !quotes;
        }
        if ((*input == '"' || *input == '\'') && *input == *(input + 1))
            input++;
        else if (*input == '"' || *input == '\'')
            quotes = !quotes;
        if (*input != ' ' && *input != '|' && *input != '&' && *input != ';' && *input != '>' && *input != '<' && !flag && !quotes)
        {
            flag = 1;
            count++;
        }
        else if (*input == ' ' || *input == '|' || *input == '&' || *input == ';' || *input == '>' || *input == '<')
            flag = 0;
        input++;
    }
    return (count);
}

int	ft_token_len(char *input, int i)
{
    size_t	len;
    char	quotes;

    len = 0;
    if (input[i] == '|' || input[i] == '&' || input[i] == ';' || input[i] == '>' || input[i] == '<')
    {
        if (input[i] == '>' && input[i + 1] == '>')
            return (2);
        return (1);
    }
    while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '&' && input[i] != ';' && input[i] != '>' && input[i] != '<')
    {
        if (input[i] == '\"' || input[i] == '\'')
        {
            quotes = input[i++];
            while (input[i] && input[i] != quotes)
                i++;
            if (input[i] == quotes)
                i++;
        }
        else
            i++;
        len++;
    }
    return (len);
}

char	**ft_create_array(char *input, t_env *env)
{
	int	i;
	int j;
	int	x;
	int	len;
	char	**array;

	i = 0;
	j = 0;
	x = 0;
	len = 0;
	array = malloc(sizeof(char *) * ft_count_tokens(input) + 1);
	if (!array)
		return (NULL);
	while (j < ft_count_tokens(input))
	{
		x = 0;
		while (input[i] == ' ')
			i++;
		if (input[i] == '$')
		{
			array[j] = ft_handle_dollar(input, env); // neue funktion
			i = i + ft_strlen(array[j]);
			j++;
		}
		else
		{
			len = ft_token_len(input, i);
			array[j] = malloc(sizeof(char) * len + 1);
			if (!array[j])
				return (NULL);
			while (input[i] && x < len)
			{
				array[j][x] = input[i];
				i++;
				x++;
			}
			array[j][x] = '\0';
			j++;
		}
	}
	array[j] = NULL;
	return (array);
}

// void	ft_tokenizer()
// {
	
// }