/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:19:36 by merdal            #+#    #+#             */
/*   Updated: 2024/10/07 16:09:59 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

/* void	print_arrays(char **arrays)
{
	if (arrays == NULL) {
		printf("Array is NULL\n");
		return;
	}

    for (int i = 0; arrays[i] != NULL; i++) {
        printf("%s\n", arrays[i]);
    }
} */

/* void	print_cmd_struct(const t_cmd *cmd)
{
	int i = 0;

	while (cmd != NULL) // Loop through each command in the linked list
	{
		printf("Arguments:\n");
		i = 0; // Reset index for arguments array
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				printf("  [%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		else
		{
			printf("  None\n");
		}
		printf("operator: %s\n", cmd->operator);
		printf("Input FD: %d\n", cmd->input_fd);
		printf("Output FD: %d\n", cmd->output_fd);	
		// Move to the next command in the list, if it exists
		if (cmd->next)
		{
			printf("Moving to next command...\n");
			cmd = cmd->next;
		}
		else
		{
			printf("No next command.\n");
			break; // Exit the loop if there is no next command
		}
	}
} */

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;

		// Free operator
		if (temp->operator)
			free(temp->operator);

		// Free args
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}

		// Free heredoc delimiter
		if (temp->heredoc_delimiter)
			free(temp->heredoc_delimiter);

		// Free the command structure itself
		free(temp);
	}
}

void ft_free_env(t_env *env) {
    if (!env)
        return;

    // Free the linked list of environment variables
    t_varlst *current = env->envp_list;
    t_varlst *next;

    while (current) {
        next = current->next;  // Store the next node
        free(current->var_name); // Free the variable name
        free(current->var_value); // Free the variable value
        free(current); // Free the current node
        current = next; // Move to the next node
    }

    // Free the environment pointer array
    if (env->envp) {
        for (int i = 0; env->envp[i] != NULL; i++) {
            free(env->envp[i]);
        }
        free(env->envp); // Free the pointer to the array itself
    }

    // Free the t_env structure
    free(env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env				*env;
	t_cmd				*cmd;
	char				*input;

	(void)argv;
	env = malloc(sizeof(t_env));
	cmd = malloc(sizeof(t_cmd));
	env->envp = envp;
	ft_init(envp, env);
	init_signal_handler();
	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	while (1)
	{
		g_signal_received = 0;
		input = ft_get_input(env);
		ft_check_input(input, env);
		add_history(input);
		cmd = ft_parser(input, env);
		// print_cmd_struct(cmd);
		ft_check_args(cmd, env);
		env->exec_flag = 0;
		ft_free_cmd(cmd);
	}
	ft_free_env(env);
	return (0);
}
