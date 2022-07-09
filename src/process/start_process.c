#include "minishell.h"

// static void ft_dups (t_cmd *cmd)
// {

// 	// else if (g_ms->count != g_ms->pipe && g_ms->pipe)
// 	// {
// 	// 	dup2(g_ms->cmd_node[g_ms->pipe - g_ms->count - 1]->fd_out, );
// 	// }

// 	else if (g_ms->count && g_ms->pipe)
// 	{
// 		pipe (cmd->pipe);
// 		cmd->fd_out = cmd->pipe[1];
// 		if (!g_ms->cmd_node[g_ms->pipe - g_ms->count]->fd_in)
// 			g_ms->cmd_node[g_ms->pipe - g_ms->count]->fd_in = cmd->pipe[0];
// 		dup2 (cmd->fd_out, STDOUT_FILENO);
// 	}

// 	return ;
// }
void ft_open_pipe (t_cmd *cmd)
{
	if (cmd->fd_in)
		dup2(cmd->fd_in, STDIN_FILENO);
	else if (g_ms->count != g_ms->pipe && g_ms->pipe)
		dup2(g_ms->cmd_node[g_ms->pipe - g_ms->count - 1]->fd_in, STDIN_FILENO);
	if (cmd->fd_out)
		dup2 (cmd->fd_out, STDOUT_FILENO);
	else if (g_ms->count && g_ms->pipe)
	{
		pipe (cmd->pipe);
		cmd->fd_out = cmd->pipe[1];
		if (!g_ms->cmd_node[g_ms->pipe - g_ms->count]->fd_in)
			g_ms->cmd_node[g_ms->pipe - g_ms->count]->fd_in = cmd->pipe[0];
		dup2 (cmd->fd_out, STDOUT_FILENO);
	}
}
void	ft_process_cmds (void)
{
	int i;
	int old_in;
	int old_out;

	i = 0;
	while (g_ms->count--)
	{
		old_in = dup(STDIN_FILENO);
		old_out = dup(STDOUT_FILENO);
		ft_open_pipe (g_ms->cmd_node[i]);
		if (is_builtin (g_ms->cmd_node[i]))
			exec_builtin(g_ms->cmd_node[i]);
		else
		 	ft_check_exec (g_ms->cmd_node[i]);
		i++;
		dup2 (old_in, STDIN_FILENO);
		dup2 (old_out, STDOUT_FILENO);
	}

	//ft_close_fds ();
	return ;
}
