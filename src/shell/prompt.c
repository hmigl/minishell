#include "minishell.h"

static void ft_save_history (char *prompt_line)
{
	if (*prompt_line)
		add_history (prompt_line);
	return ;
}

static char *ft_prompt (void)
{
	char *str;
	char *cwd;

	cwd = getcwd (0, 0);
	printf ("%s", cwd);
	str = readline("/Minishell> ");
	free (cwd);
	if (!str[0])
	{
		free (str);
		ft_prompt ();
	}
	return (str);
}

void	ft_start_shell (void)
{
	char *prompt_line;
	while (1)
	{
		prompt_line = ft_prompt ();
		ft_save_history(prompt_line);
		ft_redirect (prompt_line);
	}
}
