#include "minishell.h"

void ft_expand_var_cmd_node(t_cmd *cmd)
{
	int		i;
	char	*temp;
	int		alloc;

	alloc = 0;
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[i])
			{
				temp = ft_expand_env_var (cmd->argv[i]);
				if (temp[0])
					alloc++;
				cmd->argv[i] = temp;
				i++;
			}
	}
	return ;
}

static void ft_split_space (t_cmd *cmd)
{
	ft_convert_chars (cmd->not_parsed, ' ');
	cmd->argv = ft_split (cmd->not_parsed, 127);
}

void ft_parse (void)
{
	int i;

	g_ms->count = 0;
	i = 0;
	g_ms->n_cmd = g_ms->n_pipe + 1;
	while (g_ms->n_cmd > i)
	{
		g_ms->cmd_node[i]->not_parsed = ft_redirect(g_ms->cmd_node[i]->not_parsed);
		//chechar se tem erro no redirect (variavel :g_ms->cmd_node[i]->error)
		ft_split_space(g_ms->cmd_node[i]);
		ft_expand_var_cmd_node (g_ms->cmd_node[i]);
		g_ms->cmd_node[i]->argv = ft_save_env_vars (g_ms->cmd_node[i]);
		ft_remove_quotes_from_cmd_node (g_ms->cmd_node[i]);
		g_ms->count++;
		i++;
	}
	return ;
	//redirect (se erro, poe dentro do node e continue)
	//expandir variáveis
	//splitar comandos em space
	//checar se é builtin, atribuição, execv ou se não existe o cmd
	// se tiver atribuição fazer agora (se tiver mais de um cmd ou tiver pipe = atribuição temporária apenas)
	//o que deve acontecer se o comando é apenas um diretorio para um arquivo ou pasta?

}
