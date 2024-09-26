/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merdal <merdal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:51:08 by merdal            #+#    #+#             */
/*   Updated: 2024/09/25 11:40:59 by merdal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_set_fds(t_cmd *temp)
{
	t_cmd	*new_head;

	new_head = temp;
	while (temp->next)
	{
		if (ft_strcmp(temp->operator, ">") == 0)
			ft_fd_rdr(temp);
		else if (ft_strcmp(temp->operator, ">>") == 0)
			ft_fd_rdrapp(temp);
		else if (ft_strcmp(temp->operator, "<") == 0)
			ft_fd_rdr2(temp);
		else if (ft_strcmp(temp->operator, "<<") == 0)
			ft_fd_heredoc(temp);
		else if (ft_strcmp(temp->operator, "|") == 0)
			ft_pipe(temp);
		temp = temp->next;
	}
	return (new_head);
}


// t_cmd	*ft_set_fds(t_cmd *temp)
// {
// 	t_cmd	*new_head = temp;
	
// 	while (temp->next)
// 	{
// 		if (ft_strcmp(temp->operator, ">") == 0)
// 		{
// 			temp->output_fd = open(temp->next->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (temp->output_fd == -1)
// 			{
// 				perror("open");
// 				return (NULL);
// 			}
// 		}
// 		else if(ft_strcmp(temp->operator, ">>") == 0)
// 		{
// 			temp->output_fd = open(temp->next->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (temp->output_fd == -1)
// 			{
// 				perror("open");
// 				return (NULL);
// 			}
// 		}
// 		else if(ft_strcmp(temp->operator, "<") == 0)
// 		{
// 			temp->input_fd = open(temp->next->args[0], O_RDONLY);
// 			if (temp->input_fd == -1)
// 			{
// 				perror("open");
// 				return (NULL);
// 			}
// 		}
// 		else if(ft_strcmp(temp->operator, "<<") == 0)
// 		{
// 			int		pipe_fd[2];
// 			char	*input;

// 			if (pipe(pipe_fd) == -1)
// 			{
// 				perror("pipe");
// 				return (NULL);
// 			}
// 			while (1)
// 			{
// 				input = readline("heredoc> ");
// 				if (ft_strcmp(input, temp->next->args[0]) == 0)
// 				{
// 					free(input);
// 					break;
// 				}	
// 				write(pipe_fd[1], input, strlen(input));
// 				write(pipe_fd[1], "\n", 1);
// 				free(input);
// 			}
// 			close(pipe_fd[1]);

// 			temp->input_fd = pipe_fd[0];
// 		}
// 		else if(ft_strcmp(temp->operator, "|") == 0)
// 		{
// 			int	pipe_fd[2];
// 			if (pipe(pipe_fd) == -1)
// 			{
// 				perror("pipe");
// 				return (NULL);
// 			}
// 			temp->output_fd = pipe_fd[0];
// 			if(temp->output_fd == -1)
// 			{
// 				perror("pipe");
// 				return (NULL);
// 			}
// 			if (temp->next != NULL)
// 			{
// 				temp->next->input_fd = pipe_fd[1];
// 				if (temp->next->input_fd == -1)
// 				{
// 					perror("pipe");
// 					return (NULL);
// 				}
// 			}
// 		}
// 		temp = temp->next;
// 	}
// 	return (new_head);
// }
