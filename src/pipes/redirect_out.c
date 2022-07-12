#include "minishell.h"

static void ft_open_out (char *str, char *prompt_line, int t)
{
	char	*file_name;

	file_name = ft_file_name (prompt_line, '>');
	if (!(access(file_name, F_OK)))
	{
		if (access(file_name, W_OK) < 0)
		{
			printf ("nao pode escrever\n");
			return ;
		}
		if (t == 1)
			g_ms->cmd_node[g_ms->count]->fd_out = open (file_name, O_WRONLY | O_TRUNC);
		else
			g_ms->cmd_node[g_ms->count]->fd_out = open (file_name, O_WRONLY | O_APPEND);
	}
	else
		g_ms->cmd_node[g_ms->count]->fd_out =  open (file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	return ;
}


char	*ft_out_redirect (char *str, char *prompt_line)
{
	int i;
	int t;

	t = 0;
	i = -1;
	while (prompt_line[++i] && prompt_line[i] == '>')
	{
		if (prompt_line[i] == '>')
			t++;
	}
	ft_open_out (str, prompt_line, t);
	return (ft_trim_redirect (str));
}
