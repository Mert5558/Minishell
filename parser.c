/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:11:55 by merdal            #+#    #+#             */
/*   Updated: 2024/07/24 11:58:11 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	ft_parser(char *input, t_env *env)
{
	int	i;
	char	**array;

	i = 0;
	array = ft_create_array(char *input, t_env *env);
	while (array[i] != NULL)
	{
		
	}
}
