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
	g_ms->cmd_node = ft_calloc(alloc_cmd, sizeof(t_cmd )); // review
	return ;
}

void	ft_save_history(char *prompt_line)
{
	if (*prompt_line)
		add_history(prompt_line);
	return ;
}

char	*ft_prompt(void)
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


