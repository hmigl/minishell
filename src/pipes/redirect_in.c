#include "minishell.h"

static void ft_open_in (char *prompt_line)
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
		g_ms->cmd_node[g_ms->count].fd_in = open (file_name, O_RDONLY);
	}
	else
	{
		ms_display_error(file_name, ": No such file or directory", 0);
		g_ms->redirect_error = 1;
	}
	free (file_name);
	return ;
}

char	*ft_in_redirect (char *str, char *prompt_line)
{
	int i;

	i = 0;
	while (prompt_line[i] && prompt_line[i] == '<')
		i++;
	if (i == 1)
		ft_open_in (prompt_line);
	else
		exec_heredoc (&prompt_line[i]);
	return (ft_trim_redirect (str));
}
