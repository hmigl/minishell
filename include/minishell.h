#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

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
	char	*not_parsed;
	int		fd_in;
	int		fd_out;
	int 	error;
	int		type;
};

struct s_minishell {
	t_var	*env_var;
	t_cmd	**cmd_node;
	int		pipe;
	int		exit_code;
	int		n_cmd;
};

//  SUPPORT
void	ft_start_shell(void);
void	ms_display_error(char *id, char *err, int should_quit);
int		ft_next_occurrence (char *str, char y);

// REDIRECT
char	*ft_redirect(char *prompt_line);
char	*ft_out_redirect(char *str, char *prompt_line);
char	*ft_in_redirect(char *str, char *prompt_line);
char	*ft_file_name(char *prompt_line, char redirect);
char	*ft_trim_redirect(char *str);

// ENV
void	ft_save_local_env(char **env);
void	rm_single_node(t_var *node);
char	*ft_expand_env_var(char *cmd);

// BUILTINS
int		is_builtin(t_cmd *cmd);
void	exec_builtin(t_cmd *cmd);
void	ms_echo(char **argv);
void	ms_cd(char **argv);
void	ms_pwd(void);
void	ms_export(char *statement);
void	ms_unset(char *key);
void	ms_env(void);
void	ms_exit(char **argv);

// PARSE
int		ft_check_syntax(char *prompt_line);
void	ft_unpipe_and_alloc(char *prompt_line);
void 	ft_re_convert_chars(char *str, char convert);
void	ft_convert_chars(char *str, char convert);
void	ft_parse(void);
void	ft_remove_quotes(t_cmd *cmd);

// PROCESS
void	ft_process_cmds(void);

#endif // MINISHELL_H
