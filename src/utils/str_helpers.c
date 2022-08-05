#include "minishell.h"

int	ft_next_occurrence (char *str, char y)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == y)
			return (i);
	}
	return (-1);
}

int	is_not_spc_quote_dollar(char c)
{
	return (c != ' ' && c != '\'' && c != '\"' && c != '$');
}

int	only_space(t_cmd *cmd)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (!cmd->argv)
		return (1);
	while (cmd->argv[++i])
	{
		while (cmd->argv[i][++j])
		{
			if ((cmd->argv[i][j]) != ' ')
				return (0);
		}
		j = -1;
	}
	return (1);
}
