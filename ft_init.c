/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:39:20 by merdal            #+#    #+#             */
/*   Updated: 2024/07/12 12:14:36 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_split(char **arr)
{
    int i;

    if (!arr)
        return;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Helper function to create a new node
t_varlst *new_varlst_node(char *var_name, char *var_value)
{
    t_varlst *node = (t_varlst *)malloc(sizeof(t_varlst));
    if (!node)
        return (NULL);
    node->var_name = ft_strdup(var_name); // Assuming ft_strdup duplicates a string
    node->var_value = ft_strdup(var_value);
    node->next = NULL;
    return (node);
}

// Helper function to add a node to the end of the list
void add_varlst_node(t_varlst **head, t_varlst *new_node)
{
    t_varlst *temp;
    if (!*head)
    {
        *head = new_node;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}

// Function to initialize the variable list from envp
t_varlst *ft_init_varlst(char **envp)
{
    t_varlst *var_list = NULL;
    char **split;
    int i;

    i = 0;
    while (envp[i])
    {
        split = ft_split(envp[i], '='); // Assuming ft_split splits a string into an array
        if (split[0] && split[1]) // Check if split was successful
        {
            add_varlst_node(&var_list, new_varlst_node(split[0], split[1]));
        }
        // Assuming you have a function to free the split array
        ft_free_split(split); // Free the split array to avoid memory leaks
        i++;
    }
    return var_list;
}

// void print_var_value(t_env *env, char *key)
// {
//     t_varlst *current = env->envp_list;
//     while (current != NULL)
//     {
//         if (strcmp(current->var_name, key) == 0)
//         {
//             printf("Value: %s\n", current->var_value);
//             return;
//         }
//         current = current->next;
//     }
//     printf("Key not found.\n");
// }

void	ft_init(char **envp, t_env *env)
{
	env->envp = envp;
	env->envp_list = ft_init_varlst(envp);
	env->exit_status = 0;
}