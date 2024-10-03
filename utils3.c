/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:53:02 by merdal            #+#    #+#             */
/*   Updated: 2024/10/03 12:54:29 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_operator(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 ||
		ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0 ||
		ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

int	ft_array_len(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[len] && !ft_is_operator(array[len]))
		len++;
	return (len);
}