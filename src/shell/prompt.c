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

void ft_print_nodes(void)
{
	int i = -1;
	int j = -1;
	int k = 0;
	while (g_ms->cmd_node[++j]->not_parsed)
	{
		if (g_ms->cmd_node[j]->argv)
		{
			while (g_ms->cmd_node[j]->argv[++i])
				printf ("%s->",g_ms->cmd_node[j]->argv[i]);
		}
		printf ("\nNew command\n");
		i = -1;
	}
}

void	ft_start_shell(void) // move to main
{
	char	*prompt_line;

	while (1)
	{
		g_ms->pipe = 0;
		g_ms->n_cmd = 0;
		prompt_line = ft_prompt();
		ft_save_history(prompt_line);
		if (ft_check_syntax (prompt_line))
			continue ;
		ft_alloc_cmd(prompt_line);
		ft_unpipe_and_alloc (prompt_line);
		ft_parse ();
		ft_print_nodes();
		//ft_process_cmds ();
	}
}


// quando existirmais de um cmd, as atribuições de variáveis devem ser válidas apenas durante aquela linha de comando
// talvez uma função "there is only atribuition" pra checar se só tem atribuição, pq se existir algo além ela é atribuida localmente
