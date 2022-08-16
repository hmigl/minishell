/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:03:39 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:35:09 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_convert_chars(char *str, char convert)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += ft_next_occurrence (&str[i], str[i]);
		else if (str[i] == convert)
			str[i] = 127;
	}
	return ;
}

void	ft_re_convert_chars(char *str, char convert)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += ft_next_occurrence (&str[i], str[i]);
		else if (str[i] == 127)
			str[i] = convert;
	}
	return ;
}
