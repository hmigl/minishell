/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:11:57 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 19:11:58 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free(void *pointer)
{
	if (pointer)
		free(pointer);
	return (NULL);
}

static void	free_var_struct(t_var *var_struct)
{
	t_var	*anchor;

	while (var_struct)
	{
		anchor = var_struct;
		var_struct = var_struct->next;
		free(anchor->key);
		free(anchor->value);
		free(anchor);
	}
	return ;
}

void	*ft_free_double_pointer(char **pointer)
{
	int	i;

	i = 0;
	if (pointer)
	{
		while (pointer[i])
		{
			free(pointer[i]);
			i++;
		}
	}
	ft_free(pointer);
	return (NULL);
}

static void	free_cmd_nodes(void)
{
	int	i;

	i = 0;
	while (g_ms->total_cmd > i)
	{
		ft_free_double_pointer(g_ms->cmds[i].argv);
		ft_free(g_ms->cmds[i].cmd_path);
		ft_free(g_ms->cmds[i].n_prs);
		i++;
	}
	ft_free(g_ms->cmds);
	g_ms->cmds = NULL;
	return ;
}

void	free_all_struct(int exit)
{
	free_cmd_nodes();
	g_ms->path = ft_free_double_pointer(g_ms->path);
	free_var_struct(g_ms->local_var);
	ft_free_double_pointer(g_ms->path);
	g_ms->local_var = NULL;
	if (exit)
	{
		free_var_struct(g_ms->env_var);
		free(g_ms);
	}
	return ;
}
