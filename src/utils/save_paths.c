#include "minishell.h"


static void ft_add_slash (void)
{
	int i;
	char *step;
	char *slash;

	i = -1;
	while (g_ms->path[++i])
	{
		step = ft_strjoin(g_ms->path[i], "/");
		g_ms->path[i] = step;
	}
}

void ft_save_paths (void)
{
	t_var *anchor;

	anchor = g_ms->env_var;
	while (ft_strncmp (anchor->key, "PATH", -1))
		anchor = anchor->next;
	g_ms->path = ft_split (anchor->value, ':');
	ft_add_slash ();
	return ;
}
