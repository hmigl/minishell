/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:41:44 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:50:35 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_trim_redirect_cpy(char *str, char *rtn)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' )
		rtn[j++] = str[i++];
	while (str[i] == '<' || str[i] == '>' )
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\"' || str[i] == '\'')
		i += ft_next_occurrence (&str[i], str[i]) + 1;
	else
	{
		while (str[i] != ' ' && str[i])
			i++;
	}
	while (str[i])
		rtn[j++] = str[i++];
	free (str);
	str = NULL;
}

char	*ft_trim_redirect(char *str)
{
	int		i;
	char	*rtn;
	int		trim;

	trim = 0;
	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' )
		i++;
	while (str[i + trim] == '<' || str[i + trim] == '>' )
		trim++;
	while (str[i + trim] == ' ')
		trim++;
	if (str[i + trim] == '\"' || str[i + trim] == '\'')
		trim += ft_next_occurrence (&str[i + trim], str[i + trim]) + 1;
	else
	{
		while (str[i + trim] != ' ' && str[i + trim])
			trim++;
	}
	rtn = ft_calloc (ft_strlen(str) - trim + 1, sizeof(char));
	ft_trim_redirect_cpy (str, rtn);
	return (rtn);
}

char	*ft_file_name(char *prompt_line, char redirect)
{
	char	*file_name;
	int		i;

	i = 0;
	while (prompt_line[i] == redirect)
		i++;
	while (prompt_line[i] == ' ')
		i++;
	if (prompt_line[i] == '\"' || prompt_line[i] == '\'')
		file_name = ft_get_file_name (&prompt_line[i + 1], prompt_line[i]);
	else
		file_name = ft_get_file_name (&prompt_line[i], 0);
	return (file_name);
}

static	char	*ft_check_redirect_type(char *str, char *prompt, char redr)
{
	if (redr == '>')
		str = ft_out_redirect(str, prompt);
	else
		str = ft_in_redirect(str, prompt);
	return (str);
}

char	*ft_redirect(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += (ft_next_occurrence(&str[i], str[i]));
		else if (str[i] == '>' || str[i] == '<')
		{
			str = ft_check_redirect_type(str, &str[i], str[i]);
			i = -1;
			if (g_ms->redirect_error)
				break ;
		}
	}
	return (str);
}
