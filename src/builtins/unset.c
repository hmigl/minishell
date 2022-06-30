#include "minishell.h"

void	unset(char *key)
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
			{
				prev->next = anchor->next;
				if (anchor->next)
					anchor->next->prev = prev;
			}
			else
				g_ms->env_var = anchor->next;
			rm_single_node(anchor);
			break ;
		}
		prev = anchor;
		anchor = anchor->next;
	}
	// g_ms.exit_code = 0;
}
