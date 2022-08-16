/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:12:23 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 19:13:27 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_next_occurrence(char *str, char y)
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
	int	i;
	int	j;

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

char	*ft_get_file_name(char *prompt_line, char quote)
{
	char	*file_name;
	int		i;

	i = 0;
	if (quote)
	{
		while (prompt_line[i] != quote)
			i++;
	}
	else
	{
		while (prompt_line[i] != ' ' && prompt_line[i])
			i++;
	}
	file_name = ft_calloc (i + 1, sizeof(char));
	ft_strlcpy (file_name, prompt_line, i + 1);
	return (file_name);
}
