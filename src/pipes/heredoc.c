#include "minishell.h"

static void write_heredoc_lines(char *heredoc_line, char *delimiter, int *fd)
{
	char	*err;

	while (heredoc_line != NULL && ft_strncmp(heredoc_line, delimiter, -1))
	{
		write(STDIN_FILENO, "heredoc> ", 9);
		write(fd[1], heredoc_line, ft_strlen(heredoc_line));
		free(heredoc_line);
		heredoc_line = get_next_line(STDIN_FILENO);
		if (heredoc_line == NULL)
		{
			err = ft_strjoin("delimited by EOF - wanted ", delimiter);
			ft_putchar_fd('\n', STDERR_FILENO);
			ms_display_error("warning: heredoc ", err, 0);
			free(err);
		}
	}
}

static char * ft_found_delimiter (char *str)
{
	char *delimiter;
	char *delimiter_nl;
	int i;
	int alloc;
	char trigger;

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

	delimiter_nl = ft_strjoin( delimiter, "\n");
	ft_free (delimiter);
	return (delimiter_nl);
}
void	exec_heredoc(char *str) // , char *delimiter) ?
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
	close(fd[1]);
	g_ms->cmd_node[g_ms->count].fd_in = dup(fd[0]);
	ft_free (delimiter_nl);
	close(fd[0]);
}
