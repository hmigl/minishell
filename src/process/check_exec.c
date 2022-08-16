/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:58:53 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 19:03:19 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_exec_cmd(t_cmd *cmd)
{
	char	**envp;
	int		exit_code;

	envp = get_envp();
	exit_code = execve(cmd->cmd_path, cmd->argv, envp);
	free_all_struct(1);
	rl_clear_history();
	ft_free_double_pointer(envp);
	exit(exit_code);
}

static	void	ft_create_process(t_cmd *cmd)
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
	if (g_ms->cmds[g_ms->n_pipe - g_ms->c].fd_out)
		close (g_ms->cmds[g_ms->n_pipe - g_ms->c].fd_out);
	g_ms->exit_code = (wstatus >> 8);
}

void	ft_check_exec(t_cmd *cmd)
{
	if (cmd->argv[0] == 0)
		return ;
	if (!ft_check_access(cmd))
		ft_create_process (cmd);
	else if (!ft_check_permissions_and_directory (cmd))
		return ;
	else
	{
		ms_display_error_execve(cmd->argv[0], ": command not found", 0);
		g_ms->exit_code = 127;
	}
	return ;
}
