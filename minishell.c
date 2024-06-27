/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:19:36 by merdal            #+#    #+#             */
/*   Updated: 2024/06/27 15:24:00 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *input;

	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	while (1)
	{
		char *amk = "-- minishell -- $ ";	
		input = readline(amk);
		printf("%s\n", input);
	}
	return (0);
}