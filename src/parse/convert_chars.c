#include "minishell.h"

void ft_convert_chars (char *str, char convert)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i +=ft_next_occurrence (&str[i], str[i]);
		else if (str[i] == convert)
			str[i] = 127;
	}
	return ;
}

void ft_re_convert_chars (char *str, char convert)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i +=ft_next_occurrence (&str[i], str[i]);
		else if (str[i] == 127)
			str[i] = convert;
	}
	return ;
}
