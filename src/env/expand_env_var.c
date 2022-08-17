/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:21:36 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/17 13:18:46 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*ft_get_values_for_variable(void)
{
	int	*i;

	i = ft_calloc (sizeof(int), 3);
	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	return (i);
}

char	*ft_convert(char *content, char *key, char *cmd)
{
	int		*i;
	char	*convert;
	size_t	aux;

	i = ft_get_values_for_variable();
	aux = ft_strlen(cmd) + ft_strlen(content) - ft_strlen(key);
	convert = ft_calloc(aux, sizeof(char));
	while (cmd[++i[0]])
	{
		if (cmd[i[0]] == '$')
		{
			while (content[++i[1]])
				convert[++i[2]] = content[i[1]];
			i[0]++;
			while (cmd[i[0]] && is_not_spc_quote_dollar(cmd[i[0]]))
				i[0]++;
			break ;
		}
		else
			convert[++i[2]] = cmd[i[0]];
	}
	while (cmd[i[0]])
		convert[++i[2]] = cmd[i[0]++];
	free_two_ptrs(cmd, i);
	return (convert);
}

static char	*ft_cannot_find(char *var, char *cmd)
{
	int		i;
	int		k;
	char	*convert;

	k = -1;
	i = 1;
	while (var[i] && is_not_spc_quote_dollar(var[i]))
		i++;
	convert = ft_calloc(ft_strlen(cmd) - i + 1, sizeof(char));
	i = 0;
	while (cmd[++k] != '$' && cmd[k])
		convert[i++] = cmd[k];
	k++;
	while (cmd[k] && is_not_spc_quote_dollar(cmd[k]))
		k++;
	while (cmd[k])
		convert[i++] = cmd[k++];
	free(cmd);
	return (convert);
}

char	*ft_find(char *var, char *cmd)
{
	size_t	i;
	int		bigger;
	t_var	*anchor;

	anchor = g_ms->env_var;
	i = 1;
	if (var[i] == '?')
		return (ft_expand_exit_error (cmd));
	while (var[i] && is_not_spc_quote_dollar(var[i]))
		i++;
	while (anchor)
	{
		bigger = i - 1;
		if (ft_strlen(anchor->key) > i - 1)
			bigger = ft_strlen(anchor->key);
		if (!(ft_strncmp(anchor->key, &var[1], bigger)))
			return (ft_convert(anchor->value, anchor->key, cmd));
		else
			anchor = anchor->next;
	}
	return (ft_cannot_find(var, cmd));
}

char	*ft_expand_env_var(char *cmd)
{
	int	i;
	int	trigger;

	trigger = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\"')
			trigger = 1;
		else if (cmd[i] == '\'' && !trigger)
			i += ft_next_occurrence(&cmd[i], '\'');
		else if (cmd[i] == '$' && cmd[i + 1] != ' ' && cmd[i + 1])
		{
			cmd = ft_find(&cmd[i], cmd);
			i = -1;
		}
	}
	return (cmd);
}
