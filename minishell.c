/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:19:36 by merdal            #+#    #+#             */
/*   Updated: 2024/07/12 14:41:28 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char 	*input;
	char 	*amk;

	env = malloc(sizeof(t_env));
	amk = argv[0];
	env->envp = envp;
	ft_init(envp, env);
	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	while (1)
	{
		input = ft_get_input();
		ft_check_input(input, env);
		add_history(input);
		input = ft_handle_dollar(input, env);
		printf("%s\n", input);
	}
	return (0);
}
