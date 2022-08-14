#include "minishell.h"

void	ft_alloc_cmd(char *str)
{
	int	i;
	int	alloc_cmd;

	alloc_cmd = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == '|')
			alloc_cmd++;
		i++;
	}
	i = 0;
	g_ms->cmd_node = ft_calloc(alloc_cmd, sizeof(t_cmd));
	return ;
}

int	ft_save_history(char *prompt_line)
{
	int i;
	int only_space;

	i = -1;
	only_space = 1;

	while (prompt_line[++i])
	{
		if (prompt_line[i] != ' ')
		{
			only_space--;
			break;
		}
	}
	if (!only_space)
	{
		add_history(prompt_line);
		return (1);
	}
	return (0);
}

char	*ft_prompt(void)
{
	char	*buffer;
	char	*path;
	char	*minishell_path;

	path = NULL;
	path = getcwd(path, 0);
	minishell_path = ft_strjoin (path, "/Minishell>");
	buffer = readline(minishell_path);
	ft_free (minishell_path);
	ft_free (path);
	if (buffer == NULL)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		free_all_struct(1);
		rl_clear_history();
		exit(0);
	}
	if (!ft_save_history(buffer))
	{
		free (buffer);
		return (NULL);
	}
	return (buffer);
}
