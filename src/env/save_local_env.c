#include "minishell.h"

void	rm_single_node(t_var *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	ft_insert_nodes_in_struct(char *key, char *value)
{
	t_var	*anchor;
	t_var	*new_node;

	anchor = g_ms->env_var;
	new_node = ft_calloc(sizeof(t_var), 1);
	new_node->key = key;
	new_node->value = value;
	if (anchor == NULL)
		g_ms->env_var = new_node;
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
				return ;
			}
			anchor = anchor->next;
		}
		anchor->next = new_node;
	}
}

void	ft_save_local_env(char **env)
{
	int		i;
	char	**splited;

	i = 0;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		ft_insert_nodes_in_struct(splited[0], splited[1]);
		i++;
	}
	return ;
}
