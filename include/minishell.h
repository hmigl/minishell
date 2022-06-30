#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

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
	int		fd_in;
	int		fd_out;
};

struct s_minishell {
	t_var	*env_var;
	t_cmd	**cmd_node;
	int		pipe;
	int		exit_code;
};

//  SUPPORT
void	ft_start_shell(void);
void	ms_display_error(char *id, char *err, int should_quit);

// REDIRECT
char	*ft_redirect(char *prompt_line);
char	*ft_out_redirect(char *str, char *prompt_line);
char	*ft_in_redirect(char *str, char *prompt_line);
int		ft_next_occurrence(char *str, char y);
char	*ft_file_name(char *prompt_line, char redirect);
char	*ft_trim_redirect(char *str);

// ENV
void	ft_save_local_env(char **env);
void	rm_single_node(t_var *node);

// BUILTINS
int		is_builtin(t_cmd *cmd);
void	exec_builtin(t_cmd *cmd);
void	echo(char **args);
void	env(void);
void	pwd(void);

#endif // MINISHELL_H
