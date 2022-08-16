/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:41:42 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:56:29 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_open_out(char *prompt_line, int t)
{
	char	*file_name;

	file_name = ft_file_name (prompt_line, '>');
	if (!(access(file_name, F_OK)))
	{
		if (access(file_name, W_OK) < 0)
		{
			ms_display_error(file_name, ": Permission denied", 0);
			free (file_name);
			g_ms->redirect_error = 1;
			return ;
		}
		if (t == 1)
			g_ms->cmds[g_ms->c].fd_out = open (file_name, O_WRONLY | O_TRUNC);
		else
			g_ms->cmds[g_ms->c].fd_out = open (file_name, O_WRONLY | O_APPEND);
	}
	else
	{
		g_ms->cmds[g_ms->c].fd_out
			= open (file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	free (file_name);
	return ;
}

char	*ft_out_redirect(char *str, char *prompt_line)
{
	int	i;
	int	t;

	t = 0;
	i = -1;
	while (prompt_line[++i] && prompt_line[i] == '>')
	{
		if (prompt_line[i] == '>')
			t++;
	}
	ft_open_out (prompt_line, t);
	return (ft_trim_redirect (str));
}
