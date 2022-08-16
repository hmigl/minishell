/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:58:55 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:58:55 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_vars_amount(void)
{
	t_var	*anchor;
	int		i;

	anchor = g_ms->env_var;
	i = 0;
	while (anchor)
	{
		++i;
		anchor = anchor->next;
	}
	return (i);
}

static char	*populate_envp_with_updated_vars(t_var *env_node)
{
	char	*env_var;
	char	*buffer;

	buffer = ft_strjoin(env_node->key, "=");
	env_var = ft_strjoin(buffer, env_node->value);
	ft_free(buffer);
	return (env_var);
}

char	**get_envp(void)
{
	t_var	*anchor;
	char	**envp;
	int		env_vars;
	int		i;

	env_vars = get_env_vars_amount();
	envp = ft_calloc(env_vars + 1, sizeof(char *));
	if (envp == NULL)
		return (NULL);
	i = -1;
	anchor = g_ms->env_var;
	while (++i < env_vars)
	{
		envp[i] = populate_envp_with_updated_vars(anchor);
		anchor = anchor->next;
	}
	envp[i] = NULL;
	return (envp);
}
