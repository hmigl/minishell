/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:51:41 by hmigl             #+#    #+#             */
/*   Updated: 2022/08/12 08:51:46 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_values(char *key)
{
	t_var	*anchor;
	t_var	*prev;

	prev = NULL;
	anchor = g_ms->env_var;
	while (anchor && key)
	{
		if (!ft_strncmp(anchor->key, key, -1))
		{
			if (prev != NULL)
				prev->next = anchor->next;
			else
				g_ms->env_var = anchor->next;
			rm_single_node(anchor);
			break ;
		}
		prev = anchor;
		anchor = anchor->next;
	}
}

void	ms_unset(char **argv)
{
	int		i;

	i = -1;
	g_ms->exit_code = 0;
	if (!argv)
		return ;
	while (argv[++i] != NULL)
		unset_values(argv[i]);
}
