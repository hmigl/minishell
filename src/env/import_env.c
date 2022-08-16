/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:21:43 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:00:26 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_exit_error(char *cmd)
{
	char	*key;
	char	*value;
	char	*rtn;

	key = ft_strdup ("?");
	value = ft_itoa (g_ms->exit_code);
	rtn = ft_convert(value, key, cmd);
	ft_free(key);
	ft_free(value);
	return (rtn);
}

void	rm_single_node(t_var *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static t_var	*env_loop(char *key, char *value, t_var *var_str, t_var *new)
{
	t_var	*anchor;

	anchor = var_str;
	while (anchor->next)
	{
		if (!(ft_strcmp(anchor->key, key)))
		{
			free(anchor->value);
			free(key);
			anchor->value = value;
			free(new);
			return (var_str);
		}
		anchor = anchor->next;
	}
	anchor->next = new;
	return (var_str);
}

t_var	*add_vars_to_env(char *key_s, char *value_s, t_var *var_struct)
{
	t_var	*anchor;
	t_var	*new_node;
	char	*key;
	char	*value;

	key = ft_strdup(key_s);
	value = ft_strdup(value_s);
	anchor = var_struct;
	new_node = ft_calloc(sizeof(t_var), 1);
	new_node->key = key;
	new_node->value = value;
	if (anchor == NULL)
		var_struct = new_node;
	else
		return (env_loop(key, value, var_struct, new_node));
	return (var_struct);
}

void	ft_import_env(char **env)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		g_ms->env_var = add_vars_to_env(split[0], split[1], g_ms->env_var);
		ft_free_double_pointer (split);
		i++;
	}
	return ;
}
