#include "minishell.h"

static int ft_absoluth_path_check(t_cmd *cmd)
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
	ft_free_double_pointer(g_ms->path);
	cmd->cmd_path = 0;
	if (!ft_absoluth_path_check(cmd))
		return (0);
	ft_save_paths ();
	if (!g_ms->path)
		return (1);
	while (g_ms->path[++i])
	{
		cmd->cmd_path = ft_strjoin(g_ms->path[i], cmd->argv[0]);
		if (stat (cmd->cmd_path, &type))
		{
			free (cmd->cmd_path);
			cmd->cmd_path = NULL;
			continue;
		}
		if ((type.st_mode & S_IXUSR))
			return (0);
		free (cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	return (1);
}

static void ft_exec_cmd(t_cmd *cmd)
{
	char	**envp;
	int		exit_code;

	envp = get_envp();
	exit_code = execve(cmd->cmd_path, cmd->argv, envp);
	write (2, "Error at execve\n", 17);
	free_all_struct(1);
	rl_clear_history();
	ft_free_double_pointer(envp);
	exit(exit_code);
}

static void ft_create_process(t_cmd *cmd)
{
	int	pid;
	int	wstatus;

	wstatus = 0;
	pid = fork();
	exec_sig();
	if (pid == -1)
		printf ("Error: cannot fork the process\n");
	if (!pid)
		ft_exec_cmd(cmd);
	else
		waitpid(pid, &wstatus, 0);
	if (g_ms->cmd_node[g_ms->n_pipe - g_ms->count].fd_out)
		close (g_ms->cmd_node[g_ms->n_pipe - g_ms->count].fd_out);
	g_ms->exit_code = (wstatus >> 8);
}

void ft_check_exec (t_cmd *cmd)
{
	if (cmd->argv[0] == 0)
		return ;
	if (!ft_check_access(cmd))
		ft_create_process (cmd);
	else
	{
		ms_display_error_execve(cmd->argv[0],": command not found", 0);
		g_ms->exit_code = 127;
	}
	return ;
}
