/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:00:28 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 19:09:37 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_absoluth_path_check(t_cmd *cmd)
{
	struct stat	type;

	if (stat(cmd->argv[0], &type) != 0)
		return (1);
	if ((type.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	if ((type.st_mode & S_IXUSR))
	{
		cmd->cmd_path = ft_strdup(cmd->argv[0]);
		return (0);
	}
	return (1);
}

static	int	ft_check_path_loop(t_cmd *cmd)
{
	int			i;
	struct stat	type;

	i = -1;
	while (g_ms->path[++i])
	{
		cmd->cmd_path = ft_strjoin(g_ms->path[i], cmd->argv[0]);
		if (stat (cmd->cmd_path, &type))
		{
			free (cmd->cmd_path);
			cmd->cmd_path = NULL;
			continue ;
		}
		if ((type.st_mode & S_IXUSR))
			return (0);
		free (cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	return (1);
}

int	ft_check_access(t_cmd *cmd)
{
	ft_free_double_pointer(g_ms->path);
	cmd->cmd_path = 0;
	if (!ft_absoluth_path_check(cmd))
		return (0);
	ft_save_paths ();
	if (!g_ms->path)
		return (1);
	if (cmd->argv[0][0] == '.')
		return (1);
	return (ft_check_path_loop (cmd));
}

int	ft_check_permissions_and_directory(t_cmd *cmd)
{
	struct stat	type;
	char		*msg;

	if (stat(cmd->argv[0], &type) != 0)
		return (1);
	if ((type.st_mode & S_IFMT) == S_IFDIR)
	{
		msg = ft_strjoin(cmd->argv[0], ": Is a directory");
		printf ("minishell: %s \n", msg);
		free (msg);
		return (0);
	}
	if (!(type.st_mode & S_IXUSR))
	{
		msg = ft_strjoin(cmd->argv[0], ": Permission denied");
		printf ("minishell: %s \n", msg);
		free (msg);
		return (0);
	}
	return (1);
}
