/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_display_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:12:13 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 19:12:53 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_display_error(char *id, char *err, int should_quit)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	if (should_quit)
	{
		free_all_struct(1);
		exit(g_ms->exit_code);
	}
}

void	ms_display_error_execve(char *id, char *err, int should_quit)
{
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	if (should_quit)
	{
		free_all_struct (1);
		exit(g_ms->exit_code);
	}
}
