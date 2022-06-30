#include "minishell.h"

void	env(void)
{
	t_var *anchor;

    anchor = g_ms->env_var;
	while (anchor)
	{
		printf("%s=%s\n", anchor->key, anchor->value);
		anchor = anchor->next;
	}
	//g_minishell.exit_code = 0;
}
