#include "minishell.h"

static void ft_open_in (char *str, char *prompt_line, int t)
{
	char	*file_name;
	int		fd_out;

	file_name = ft_file_name (prompt_line, '>');
	if (!(access(file_name, F_OK)))
	{
		if (!access(file_name, W_OK))
		{
			printf ("nao pode escrever\n");
			return ;
		}
		if (t == 1)
			fd_out = open (file_name, O_WRONLY | O_TRUNC);
		else
			fd_out = open (file_name, O_WRONLY | O_APPEND);
	}
	else
		fd_out =  open (file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	return ;
}


char	*ft_in_redirect (char *str, char *prompt_line)
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
	ft_open_in (str, prompt_line, t);
	return (ft_trim_redirect (str));
}
