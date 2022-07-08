#include "minishell.h"

void	rm_single_node(t_var *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

t_var	*ft_insert_nodes_in_struct(char *key, char *value, t_var *var_struct)
{
	t_var	*anchor;
	t_var	*new_node;

	anchor = var_struct;
	new_node = ft_calloc(sizeof(t_var), 1);
	new_node->key = key;
	new_node->value = value;
	if (anchor == NULL)
		var_struct = new_node;
	else
	{
		while (anchor->next)
		{
			if (!(ft_strcmp(anchor->key, key)))
			{
				free(anchor->value);
				free(key);
				anchor->value = value;
				free(new_node);
				return (var_struct) ;
			}
			anchor = anchor->next;
		}
		anchor->next = new_node;
	}
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
		g_ms->env_var = ft_insert_nodes_in_struct(split[0], split[1], g_ms->env_var);
		i++;
	}
	return ;
}
