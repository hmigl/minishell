#include "minishell.h"

static void ft_open_in (char *str, char *prompt_line)
{
	char	*file_name;

	file_name = ft_file_name (prompt_line, '<');
	if (!(access(file_name, F_OK)))
	{
		if (access(file_name, R_OK) < 0)
		{
			printf ("nao tem acesso\n");
			return ;
		}
		g_ms->cmd_node[g_ms->count].fd_in = open (file_name, O_RDONLY);
	}
	else
		printf ("arquivo não existe\n");
	return ;
}

char	*ft_in_redirect (char *str, char *prompt_line)
{
	int i;

	i = 0;
	while (prompt_line[i] && prompt_line[i] == '<')
		i++;
	ft_open_in (str, prompt_line);
	return (ft_trim_redirect (str));
}
