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

void	exec_heredoc(t_cmd *cmd) // , char *delimiter) ?
{
	int		fd[2];
	char	*heredoc_line;
	char	*delimiter;

	delimiter = "EOL\n"; // strjoin(strdup(delimiter), "\n");
	heredoc_line = ft_strdup("");
	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	// heredoc_stdin_sig();
	write_heredoc_lines(heredoc_line, delimiter, fd);
	// ft_free(delimiter);
	// ft_free(heredoc_line);
	close(fd[1]);
	cmd->fd_in = dup(fd[0]);
	close(fd[0]);
}
