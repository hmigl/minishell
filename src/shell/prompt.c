#include "minishell.h"

static void	ft_alloc_cmd(char *str)
{
	int	i;
	int	alloc_cmd;

	alloc_cmd = 2;
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
	while (alloc_cmd--)
		g_ms->cmd_node[i++] = ft_calloc(alloc_cmd, sizeof(t_cmd));
}

static void	ft_save_history(char *prompt_line)
{
	if (*prompt_line)
		add_history(prompt_line);
	return ;
}

static char	*ft_prompt(void)
{
	char	*str;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("%s", cwd);
	str = readline("/Minishell> ");
	free(cwd);
	if (!str[0])
	{
		free(str);
		ft_prompt();
	}
	return (str);
}

void	ft_start_shell(void)
{
	char	*prompt_line;

	while (1)
	{
		g_ms->pipe = 0;
		prompt_line = ft_prompt();
		ft_save_history(prompt_line);
		ft_alloc_cmd(prompt_line);
		prompt_line = ft_redirect(prompt_line);
		printf("%s\n", prompt_line);
	}
}
