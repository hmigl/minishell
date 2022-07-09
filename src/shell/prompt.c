#include "minishell.h"

void	ft_alloc_cmd(char *str)
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

void	ft_print_nodes(void)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = 0;
	while (g_ms->cmd_node[++j]->not_parsed)
	{
		printf ("New command\n");
		if (g_ms->cmd_node[j]->argv)
		{
			while (g_ms->cmd_node[j]->argv[++i])
				printf("%s->", g_ms->cmd_node[j]->argv[i]);
		}
		printf("\n");
		i = -1;
	}
}
// quando existirmais de um cmd, as atribuições de variáveis devem ser válidas
// apenas durante aquela linha de comando talvez uma função "there is only
// atribuition" pra checar se só tem atribuição, pq se existir algo além ela é
// atribuida localmente
