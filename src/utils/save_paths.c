/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:12:16 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 19:15:16 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_copy_paths(char *cwd_path)
{
	int		i;
	char	**step;

	i = 0;
	while (g_ms->path[i])
		i++;
	step = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (g_ms->path[++i])
		step[i] = ft_strdup(g_ms->path[i]);
	step[i] = cwd_path;
	ft_free_double_pointer (g_ms->path);
	g_ms->path = step;
}

static	void	ft_save_current_path(void)
{
	char	*cwd_path;

	cwd_path = NULL;
	cwd_path = getcwd(cwd_path, 0);
	ft_copy_paths(cwd_path);
}

static	void	ft_add_slash(void)
{
	int		i;
	char	*step;

	i = -1;
	while (g_ms->path[++i])
	{
		step = ft_strjoin(g_ms->path[i], "/");
		free (g_ms->path[i]);
		g_ms->path[i] = step;
	}
}

void	ft_save_paths(void)
{
	t_var	*anchor;

	anchor = g_ms->env_var;
	while (ft_strncmp (anchor->key, "PATH", -1))
	{
		anchor = anchor->next;
		if (!anchor)
			return ;
	}
	g_ms->path = ft_split (anchor->value, ':');
	ft_save_current_path();
	ft_add_slash ();
	return ;
}
