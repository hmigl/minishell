/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:41:39 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:55:54 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_open_in(char *prompt_line)
{
	char	*file_name;

	file_name = ft_file_name (prompt_line, '<');
	if (!(access(file_name, F_OK)))
	{
		if (access(file_name, R_OK) < 0)
		{
			ms_display_error(file_name, ": Permission denied", 0);
			free (file_name);
			g_ms->redirect_error = 1;
			return ;
		}
		g_ms->cmds[g_ms->c].fd_in = open (file_name, O_RDONLY);
	}
	else
	{
		ms_display_error(file_name, ": No such file or directory", 0);
		g_ms->redirect_error = 1;
	}
	free (file_name);
	return ;
}

char	*ft_in_redirect(char *str, char *prompt_line)
{
	int	i;

	i = 0;
	while (prompt_line[i] && prompt_line[i] == '<')
		i++;
	if (i == 1)
		ft_open_in(prompt_line);
	else
	{
		while (ft_isspace(prompt_line[i]))
			++i;
		exec_heredoc(&prompt_line[i]);
	}
	return (ft_trim_redirect(str));
}
