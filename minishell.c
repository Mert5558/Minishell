/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:19:36 by merdal            #+#    #+#             */
/*   Updated: 2024/07/02 11:50:39 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	char *input;
	char *amk;
	
	amk = argv[0];
	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	while (1)
	{
		input = ft_get_input();
		//printf("%s\n", input);
		ft_check_input(input);
		add_history(input);
	}
	return (0);
}
