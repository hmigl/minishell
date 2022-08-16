/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:03:42 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:55:54 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_var_cmd_node(t_cmd *cmd)
{
	int		i;
	char	*temp;
	int		alloc;

	alloc = 0;
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[i])
		{
			temp = ft_expand_env_var (cmd->argv[i]);
			if (temp[0])
				alloc++;
			cmd->argv[i] = temp;
			i++;
		}
	}
	return ;
}

static	void	ft_split_space(t_cmd *cmd)
{
	ft_convert_chars (cmd->n_prs, ' ');
	cmd->argv = ft_split (cmd->n_prs, 127);
}

void	ft_parse(void)
{
	int	i;

	g_ms->c = 0;
	i = -1;
	while (g_ms->total_cmd > ++i)
	{
		g_ms->cmds[i].n_prs = ft_redirect(g_ms->cmds[i].n_prs);
		if (g_ms->redirect_error)
		{
			g_ms->exit_code = 1;
			g_ms->cmds[i].redirect_error = 1;
			g_ms->redirect_error = 0;
			g_ms->c++;
			continue ;
		}
		ft_split_space(&g_ms->cmds[i]);
		ft_expand_var_cmd_node (&g_ms->cmds[i]);
		g_ms->cmds[i].argv = ft_save_env_vars (&g_ms->cmds[i]);
		ft_remove_quotes_from_cmd_node (&g_ms->cmds[i]);
		g_ms->c++;
	}
	return ;
}
