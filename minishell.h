/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:07:42 by merdal            #+#    #+#             */
/*   Updated: 2024/10/18 20:03:56 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>				//PATH_MAX
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_cmd
{
	char			*operator;
	char			**args;
	int				input_fd;
	int				output_fd;
	char			*heredoc_delimiter;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_varlst
{
	char			*var_name;
	char			*var_value;
	struct s_varlst	*next;
}t_varlst;

typedef struct s_env
{
	char		**envp;
	t_varlst	*envp_list;
	long long	exit_status;
	int			exec_flag;
}t_env;

//_______________________minishell.c_______________________________
void		shell_loop(t_cmd *cmd, t_env *env);

//_______________________ft_parser.c_______________________________
t_cmd		*ft_parser(char *input, t_env *env);
t_cmd		*ft_set_fds(t_cmd *temp);

//_______________________tokenize.c________________________________
char		**ft_create_array(char *input, t_env *env);

//_______________________utils.c___________________________________
int			ft_token_len(char *input, int i);
int			ft_count_tokens(char *input);
void		ft_return_and_exit(char *error, int exit_status, t_env *env);
void		ft_fd_rdr(t_cmd *temp);
void		ft_fd_rdrapp(t_cmd *temp);
void		ft_fd_rdr2(t_cmd *temp);
void		ft_pipe(t_cmd *temp);
int			ft_is_operator(char *str);
int			ft_array_len(char **array, int i);
void		ft_return_and_exit(char *error, int exit_status, t_env *env);
int			ft_token_len(char *input, int i);
void		ft_fd_heredoc(t_cmd *temp);
void		ft_heredoc_process(t_cmd *temp, int pipe_fd);
int			ft_isspace(char c);
char		**ft_init_op(void);
char		*ft_cut(char *input, int i, int len);

//_______________________input.c___________________________________
char		*ft_get_input(t_env *env);
int			ft_check_input(char *input, t_env *env);

//_______________________input2.c__________________________________
int			ft_check_syntax(char *input, t_env *env);
int			ft_check_op(char *input, t_env *env);
int			ft_check_syntax_op(char *input, t_env *env);

//_______________________handle_dollar.c___________________________
char		*ft_handle_dollar(char *input, t_env *env);

//_______________________ft_init.c_________________________________
void		ft_free_split(char **arr);
void		ft_init(char **envp, t_env *env);
void		add_varlst_node(t_varlst **head, t_varlst *new_node);
t_varlst	*new_varlst_node(char *var_name, char *var_value);

//_______________________ft_child_process.c___________________________
void		child_process(t_cmd *cmd, t_env *env);
void		wait_child_process(t_cmd *cmd, t_env *env, int pid);
void		check_executable(t_cmd *cmd, t_env *env);
void		close_unused_fds_in_child(t_cmd *cmd);
void		redirect_fd(t_cmd *cmd);

//_______________________ft_check_args.c___________________________
void		*ft_check_args(t_cmd *cmd, t_env *env);
void		execute_parent(t_cmd *cmd, t_env *env);
void		execute_child(t_cmd *cmd, t_env *env);

//_______________________ft_pipe_execution.c_______________________
void		execute_pipe(t_cmd **cmd, t_env *env);
void		fork_child_processes(t_cmd *cmd, t_env *env,
				pid_t *pid, int num_cmds);
void		close_fds_in_parent(t_cmd *cmd, int num_cmds);
void		wait_for_children(t_cmd *cmd, t_env *env, pid_t *pid, int num_cmds);

//_______________________ft_echo.c_________________________________
char		*ft_append_char_struct(t_cmd *cmd, int i);
void		ft_echo(t_cmd *cmd);

//_______________________ft_cd.c___________________________________
void		ft_cd(t_cmd *cmd, t_env *env);
void		check_home_path(t_varlst *varlst, char **path);

//_______________________ft_pwd.c__________________________________
void		ft_pwd(void);

//_______________________ft_exe.c__________________________________
void		ft_exe(t_cmd *cmd, t_env *env);
void		ft_exe2(t_cmd *cmd, t_env *env, char **tmp_path);
void		ft_exe3(t_cmd *cmd, t_env *env, char *tmp, char **tmp_path);

//_______________________ft_export.c_______________________________
void		ft_export(t_cmd *cmd, t_env *env);
void		cmd_export(t_varlst *templst);
int			get_var_str(t_cmd *cmd, char **var_name, char **var_value, int i);
int			check_varlst(t_varlst *templst, char *var_name,
				char *var_value, char *args);

//_______________________ft_env.c__________________________________
void		ft_env(t_env *env);

//_______________________ft_unset.c_________________________________
void		ft_unset(t_cmd *cmd, t_env *env);

//_______________________ft_exit.c_________________________________
void		ft_exit(t_cmd *cmd, t_env *env);
int			ft_check_alpha(char *str);

//_______________________ft_clear.c_________________________________
void		ft_clear(void);

//_______________________signal_handler.c___________________________
void		signal_handler(int signum);
void		child_signal_handler(int signum);
void		init_signal_handler(void);

//_______________________free_memory.c______________________________
void		free_all(t_cmd *cmd, t_env *env);
void		free_cmd(t_cmd *cmd);
void		free_env_lst(t_env *env);

#endif