#include "minishell.h"


static int ft_absoluth_path_check (t_cmd *cmd)
{
	struct stat	type;

	if (stat(cmd->argv[0], &type))
		return (1);
	if ((type.st_mode & S_IXUSR))
	{
		cmd->cmd_path = ft_strdup(cmd->argv[0]);
		return (0);
	}
	return (1);

}
static int	ft_check_access(t_cmd *cmd)
{
	int	i;
	struct stat	type;

	i = -1;
	cmd->cmd_path = 0;
	if (!ft_absoluth_path_check(cmd))
		return (0);
	ft_save_paths ();
	while (g_ms->path[++i])
	{
		cmd->cmd_path = ft_strjoin(g_ms->path[i], cmd->argv[0]);
		if (stat (cmd->cmd_path, &type))
			continue;
		if ((type.st_mode & S_IXUSR))
			return (0);
		free (cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	return (1);
}

static void ft_exec_cmd (t_cmd *cmd)
{
	if (execve (cmd->cmd_path, cmd->argv, g_ms->path))
		write (2, "Error\n", 7);
}

static void ft_create_process (t_cmd *cmd)
{
	int	pid;
	int	wstatus;

	pid = fork ();
	exec_sig();
	if (pid == -1)
		printf ("Error: cannot fork the process\n");
	if (!pid)
		ft_exec_cmd(cmd);
	else
		waitpid(pid, &wstatus, 0);
	if (g_ms->cmd_node[g_ms->n_pipe - g_ms->count].fd_out)
		close (g_ms->cmd_node[g_ms->n_pipe - g_ms->count].fd_out);
}

void ft_check_exec (t_cmd *cmd)
{
	if (!ft_check_access(cmd))
		ft_create_process (cmd);
	else
		printf ("Erro check path FT_CHECK_EXEC\n");
	return ;
}
