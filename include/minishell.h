/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:17:34 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/17 13:18:23 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>

typedef struct s_var		t_var;
typedef struct s_minishell	t_minishell;
typedef struct s_cmd		t_cmd;

extern t_minishell			*g_ms;

struct s_var {
	char	*key;
	char	*value;
	t_var	*next;
	t_var	*prev;
};

struct s_cmd {
	char	**argv;
	char	*cmd_path;
	char	*n_prs;
	int		redirect_error;
	int		pipe[2];
	int		fd_in;
	int		fd_out;
	int		error;
};

struct s_minishell {
	t_var	*env_var;
	t_var	*local_var;
	t_cmd	*cmds;
	int		total_cmd;
	int		redirect_error;
	char	**path;
	int		c;
	int		pipe[2];
	int		n_pipe;
	int		exit_code;
	int		n_cmd;
	int		std_in;
	int		std_out;
};

//  SUPPORT
void	ms_display_error(char *id, char *err, int should_quit);
void	ms_display_error_execve(char *id, char *err, int should_quit);
int		ft_next_occurrence(char *str, char y);
void	*ft_free_double_pointer(char **pointer);
void	ft_save_paths(void);
int		ft_next_occurrence(char *str, char y);
void	free_all_struct(int exit);
void	stdin_sig(void);
void	exec_sig(void);
void	heredoc_stdin_sig(void);
char	*ft_prompt(void);
int		ft_save_history(char *prompt_line);
void	ft_alloc_cmd(char *str);
char	*get_next_line(int fd);
void	*ft_free(void *pointer);
int		is_not_spc_quote_dollar(char c);
int		only_space(t_cmd *cmd);
void	welcome(void);
char	*ft_get_file_name(char *prompt_line, char quote);
void	free_two_ptrs(void *ptr1, void *ptr2);

// REDIRECT
void	exec_heredoc(char *delimiter);
char	*ft_redirect(char *prompt_line);
char	*ft_out_redirect(char *str, char *prompt_line);
char	*ft_in_redirect(char *str, char *prompt_line);
char	*ft_file_name(char *prompt_line, char redirect);
char	*ft_trim_redirect(char *str);

// ENV
void	ft_import_env(char **env);
t_var	*add_vars_to_env(char *key, char *value, t_var *var_struct);
void	rm_single_node(t_var *node);
char	**ft_save_env_vars(t_cmd *cmd);
int		ft_have_a_var_to_save(char *str);
char	*ft_expand_exit_error(char *cmd);
char	*ft_convert(char *content, char *key, char *cmd);

// EXPANSION
char	*ft_expand_env_var(char *cmd);
char	*ft_find(char *variable, char *command);

// BUILTINS
int		is_builtin(t_cmd *cmd);
void	exec_builtin(t_cmd *cmd);
void	ms_echo(char **argv);
void	ms_cd(char **argv);
void	ms_pwd(void);
void	ms_export(char **argv);
void	ms_unset(char **argv);
void	unset_values(char *key);
void	ms_env(void);
void	ms_exit(char **argv);

// PARSE
int		ft_check_syntax(char *prompt_line);
void	ft_unpipe_and_alloc(char *prompt_line);
void	ft_re_convert_chars(char *str, char convert);
void	ft_convert_chars(char *str, char convert);
void	ft_parse(void);
void	ft_remove_quotes_from_cmd_node(t_cmd *cmd);
char	**ft_remove_var_atrib_and_equals(char **argv);
char	*ft_remove_quote_from_str(char *argv);
int		ft_quote_error_msg(char *prompt_line);
int		ft_backslash_error_msg(char *prompt_line);
int		ft_redirect_error_msg(char *prompt_line);
int		ft_pipe_error_msg(char *prompt_line);
int		ft_check_after_redirect(char *str, char redirect);
int		ft_check_after_pipe(char *str);

// PROCESS
void	ft_process_cmds(void);
void	ft_check_exec(t_cmd *cmd);
char	**get_envp(void);
void	ft_return_standard_exit(void);
int		ft_check_access(t_cmd *cmd);
int		ft_check_permissions_and_directory(t_cmd *cmd);

#endif
