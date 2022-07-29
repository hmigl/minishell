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

