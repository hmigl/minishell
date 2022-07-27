#include "minishell.h"

static void ft_alloc_in_cmd_node (char **str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		g_ms->cmd_node[i].not_parsed = ft_strdup(str[i]);
	}
	return ;
}

static char **ft_split_unpipe (char *prompt_line)
{
	char **temp;

	ft_convert_chars (prompt_line, '|');
	temp = ft_split (prompt_line, 127);
	free (prompt_line);
	return (temp);
}

static void ft_count_pipes (char *prompt_line)
{
	int i;

	i = -1;
	while (prompt_line[++i])
	{

		if (prompt_line[i] == '\'' || prompt_line[i] == '\"')
			i += (ft_next_occurrence (&prompt_line[i], prompt_line[i]));
		else if (prompt_line[i] == '|')
			g_ms->n_pipe++;
	}
	return ;
}

void	ft_unpipe_and_alloc (char *prompt_line)
{
	char **str;
	ft_count_pipes (prompt_line);
	str = ft_split_unpipe (prompt_line);
	ft_alloc_in_cmd_node (str);
	ft_free_double_pointer (str);
	return ;

}


