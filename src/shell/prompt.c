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

	buffer = readline("/Minishell> ");
	if (buffer == NULL)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		free_all_struct(1);
		rl_clear_history();
		exit(0);
	}
	if (!buffer[0])
	{
		free(buffer);
		buffer = ft_prompt();
	}
	if (!ft_save_history(buffer))
	{
		free (buffer);
		return (NULL);
	}
	return (buffer);
}
