/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:19:36 by merdal            #+#    #+#             */
/*   Updated: 2024/07/21 13:11:01 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_arrays(char **arrays)
{
    if (arrays == NULL) {
        printf("Array is NULL\n");
        return;
    }

    for (int i = 0; arrays[i] != NULL; i++) {
        printf("%s\n", arrays[i]);
    }
}

int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char 	*input;
	char 	*amk;
	char **array;

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
		array = ft_create_array(input, env);
		print_arrays(array);
	}
	return (0);
}
