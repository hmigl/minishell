/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:51:08 by hmigl             #+#    #+#             */
/*   Updated: 2022/08/12 08:51:46 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_cmd *cmd)
{
	if (cmd->argv == NULL)
		return ;
	if (!(ft_strncmp(cmd->argv[0], "echo", -1)))
		ms_echo(cmd->argv);
	if (!(ft_strncmp(cmd->argv[0], "cd", -1)))
		ms_cd(cmd->argv);
	if (!(ft_strncmp(cmd->argv[0], "pwd", -1)))
		ms_pwd();
	if (!(ft_strncmp(cmd->argv[0], "export", -1)))
		ms_export(cmd->argv);
	if (!(ft_strncmp(cmd->argv[0], "unset", -1)))
		ms_unset(cmd->argv);
	if (!(ft_strncmp(cmd->argv[0], "env", -1)))
		ms_env();
	if (!(ft_strncmp(cmd->argv[0], "exit", -1)))
		ms_exit(cmd->argv);
}
