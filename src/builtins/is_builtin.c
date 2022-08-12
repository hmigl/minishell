/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:51:08 by hmigl             #+#    #+#             */
/*   Updated: 2022/08/12 08:51:46 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->argv[0])
		return (0);
	if (!(ft_strncmp(cmd->argv[0], "echo", -1)))
		return (1);
	if (!(ft_strncmp(cmd->argv[0], "cd", -1)))
		return (1);
	if (!(ft_strncmp(cmd->argv[0], "pwd", -1)))
		return (1);
	if (!(ft_strncmp(cmd->argv[0], "export", -1)))
		return (1);
	if (!(ft_strncmp(cmd->argv[0], "unset", -1)))
		return (1);
	if (!(ft_strncmp(cmd->argv[0], "env", -1)))
		return (1);
	if (!(ft_strncmp(cmd->argv[0], "exit", -1)))
		return (1);
	return (0);
}
