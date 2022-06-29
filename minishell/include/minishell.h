#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

typedef struct s_var{
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_minishell
{
	t_var	*env_var;
}	t_minishell;

t_minishell	*g_global;


// FUNCTIONS

void	ft_save_local_env (char **env);
void	ft_start_shell (void);
void	ft_redirect (char *prompt_line);
char	*ft_in_redirect (char *str, char *prompt_line);
int		ft_next_occurrence (char *str, char y);
char	*ft_file_name (char *prompt_line, char redirect);
char	*ft_trim_redirect (char *str);

#endif // MINISHELL_H
