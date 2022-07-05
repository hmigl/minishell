#include "minishell.h"

void	ms_env(void)
{
	t_var *anchor;

	anchor = g_ms->env_var;
	while (anchor)
	{
		printf("%s=%s\n", anchor->key, anchor->value);
		anchor = anchor->next;
	}
	g_ms->exit_code = 0;
}
