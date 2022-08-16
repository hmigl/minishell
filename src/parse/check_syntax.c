/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:03:35 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:34:12 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_out(char *str)
{
	int	i;
	int	n_redirect;

	i = 0;
	n_redirect = 1;
	while (str[++i] && n_redirect < 3)
	{
		if (str[i] == '>')
			n_redirect++;
		else if (str[i] == '<')
			return (-1);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i += ft_next_occurrence (&str[i], str[i]);
			return (i);
		}
		else if (str[i] == '|')
			return (-1);
		else if (str[i] >= 33 && str[i] <= 126)
			return (i + 1);
	}
	return (-1);
}

static int	ft_check_in(char *str)
{
	int	i;
	int	n_redirect;

	i = 0;
	n_redirect = 1;
	while (str[++i] && n_redirect < 3)
	{
		if (str[i] == '<')
			n_redirect++;
		else if (str[i] == '>')
			return (-1);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i += ft_next_occurrence (&str[i], str[i]);
			return (i);
		}
		else if (str[i] == '|')
			return (-1);
		else if (str[i] >= 33 && str[i] <= 126)
			return (i + 1);
	}
	return (-1);
}

int	ft_check_after_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			return (-1);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i += ft_next_occurrence(&str[i], str[i]);
			return (i);
		}
		else if (str[i] >= 33 && str[i] <= 126)
			return (i + 1);
	}
	return (-1);
}

int	ft_check_after_redirect(char *str, char redirect)
{
	if (redirect == '>')
		return (ft_check_out(str));
	else
		return (ft_check_in(str));
}

int	ft_check_syntax(char *prompt_line)
{
	if (ft_quote_error_msg(prompt_line)
		|| ft_backslash_error_msg (prompt_line)
		|| ft_pipe_error_msg(prompt_line)
		|| ft_redirect_error_msg (prompt_line))
		return (1);
	return (0);
}
