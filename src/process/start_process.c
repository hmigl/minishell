#include "minishell.h"


static void	exec_process (t_cmd *cmd)
{
	printf ("%s\n", cmd->not_parsed);
	exit(0);
}


void	ft_process_cmds (void)
{
	int pid;
	while (g_ms->n_cmd <= g_ms->pipe)
	{


			exec_process(g_ms->cmd_node[g_ms->n_cmd]);

		g_ms->n_cmd++;
	}
}
