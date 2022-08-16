/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:41:37 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:55:54 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	delimiter_coincides(char *heredoc_line, char *delimiter, int fd)
{
	if (!ft_strncmp(heredoc_line, delimiter, sizeof(delimiter)))
		return (1);
	write(fd, heredoc_line, ft_strlen(heredoc_line));
	write(fd, "\n", 1);
	ft_free(heredoc_line);
	return (0);
}

static void	write_heredoc_lines(char *heredoc_line, char *delimiter, int *fd)
{
	char	*err;

	while (1)
	{
		heredoc_line = readline("heredoc> ");
		if (heredoc_line == NULL)
		{
			err = ft_strjoin("delimited by EOF - wanted ", delimiter);
			ft_putchar_fd('\n', STDERR_FILENO);
			ms_display_error("warning: heredoc ", err, 0);
			free(err);
			break ;
		}
		else if (delimiter_coincides(heredoc_line, delimiter, fd[1]))
		{
			ft_free(heredoc_line);
			break ;
		}
	}
}

static char	*alloc_delmiter(char *str)
{
	int		i;
	char	*delimiter;
	char	trigger;
	int		alloc;

	i = -1;
	alloc = 0;
	trigger = 0;
	while (str[++i] && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			trigger = str[i];
			while (str[++i] != trigger)
				alloc++;
		}
		else
			alloc++;
	}
	delimiter = ft_calloc(sizeof(char), alloc + 1);
	return (delimiter);
}

static char	*ft_found_delimiter(char *str)
{
	char	*delimiter;
	char	*delimiter_nl;
	char	trigger;
	int		i;
	int		alloc;

	delimiter = alloc_delmiter(str);
	i = -1;
	alloc = -1;
	while (str[++i] && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			trigger = str[i];
			while (str[++i] != trigger)
				delimiter[++alloc] = str[i];
		}
		else
			delimiter[++alloc] = str[i];
	}
	delimiter_nl = ft_strdup(delimiter);
	ft_free(delimiter);
	return (delimiter_nl);
}

void	exec_heredoc(char *str)
{
	int		fd[2];
	char	*heredoc_line;
	char	*delimiter_nl;

	delimiter_nl = ft_found_delimiter(str);
	heredoc_line = ft_strdup("");
	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	heredoc_stdin_sig();
	write_heredoc_lines(heredoc_line, delimiter_nl, fd);
	g_ms->cmds[g_ms->c].fd_in = dup(fd[0]);
	close(fd[1]);
	ft_free(delimiter_nl);
	close(fd[0]);
	ft_free(heredoc_line);
}
