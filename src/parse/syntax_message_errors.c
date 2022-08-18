/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_message_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:10:35 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/18 11:05:21 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote_error_msg(char *prompt_line)
{
	int	i;

	i = -1;
	while (prompt_line[++i])
	{
		if (prompt_line[i] == '\'' || prompt_line[i] == '\"' )
		{
			if (ft_next_occurrence(&prompt_line[i], prompt_line[i]) == -1)
			{
				ms_display_error("quote>: ", "command not found", 0);
				return (1);
			}
			i += ft_next_occurrence (&prompt_line[i], prompt_line[i]);
		}
	}
	return (0);
}

int	ft_backslash_error_msg(char *prompt_line)
{
	int	i;

	i = -1;
	while (prompt_line[++i])
	{
		if (prompt_line[i] == '\'' || prompt_line[i] == '\"' )
			i += ft_next_occurrence (&prompt_line[i], prompt_line[i]);
		else if (prompt_line[i] == '\\')
		{
			ms_display_error("backslash>: ", "command not found", 0);
			g_ms->exit_code = 2;
			return (1);
		}
	}
	return (0);
}

int	ft_pipe_error_msg(char *prompt_line)
{
	int	i;
	int	error;

	i = -1;
	while (prompt_line[++i])
	{
		if (prompt_line[i] == '\'' || prompt_line[i] == '\"' )
			i += ft_next_occurrence (&prompt_line[i], prompt_line[i]);
		else if (prompt_line[i] == '|')
		{
			error = ft_check_after_pipe(&prompt_line[i]);
			if (error == -1)
			{
				ms_display_error("syntax error ", "near unexpected token", 0);
				g_ms->exit_code = 2;
				return (1);
			}
			i += error;
		}
	}
	return (0);
}

int	ft_redirect_error_msg(char *prompt_line)
{
	int	i;
	int	error;

	i = -1;
	while (prompt_line[++i])
	{
		if (prompt_line[i] == '\'' || prompt_line[i] == '\"' )
			i += ft_next_occurrence (&prompt_line[i], prompt_line[i]);
		else if (prompt_line[i] == '>' || prompt_line[i] == '<')
		{
			error = ft_check_after_redirect(&prompt_line[i], prompt_line[i]);
			if (error == -1)
			{
				ms_display_error("syntax error ", "near unexpected token", 0);
				g_ms->exit_code = 2;
				return (1);
			}
			i += error - 1;
		}
	}
	return (0);
}
