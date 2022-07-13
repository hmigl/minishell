#include "minishell.h"

 void ft_open_pipe (t_cmd *cmd)
{
	if (g_ms->count)
		pipe (cmd->pipe);
	if (cmd->fd_in)
		dup2(cmd->fd_in, STDIN_FILENO);
	else if (g_ms->count != g_ms->n_pipe && g_ms->n_pipe)
		dup2(g_ms->cmd_node[g_ms->n_cmd - 1].pipe[0], STDIN_FILENO);
	if (cmd->fd_out)
		dup2 (cmd->fd_out, STDOUT_FILENO);
	else if (g_ms->count && g_ms->n_pipe)
		dup2 (cmd->pipe[1], STDOUT_FILENO);
}

void	ft_process_cmds (void)
{
	int i;
	int old_in;
	int old_out;

	g_ms->n_cmd = 0;
	i = 0;
	old_in = dup(STDIN_FILENO);
	old_out = dup(STDOUT_FILENO);
	while (g_ms->count--)
	{
		ft_open_pipe (&g_ms->cmd_node[i]);
		if (is_builtin (&g_ms->cmd_node[i]))
			exec_builtin(&g_ms->cmd_node[i]);
		else
		 	ft_check_exec (&g_ms->cmd_node[i]);
		if (g_ms->n_cmd)
			close (g_ms->cmd_node[i - 1].pipe[0]);
		close (g_ms->cmd_node[i].pipe[1]);
		if (g_ms->count == 1)
			dup2 (old_out, STDOUT_FILENO);
		g_ms->n_cmd++;
		i++;
	}
	free_all_struct (0);
	dup2 (old_out, STDOUT_FILENO);
	dup2 (old_in, STDIN_FILENO);
	return ;
}
