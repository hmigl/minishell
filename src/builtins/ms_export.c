#include "minishell.h"

static void	show_names_n_values(void);

void	ms_export(char *statement)
{
	int		i;
	char	*key;
	char	*value;
	char	**splited;

	i = 0;
	if (!statement)
	{
		show_names_n_values();
		g_ms->exit_code = 0;
		return ;
	}
	splited = ft_split(statement, '=');
	key = splited[0];
	value = splited[1];
	add_vars_to_env(key, value, g_ms->env_var);
	g_ms->exit_code = 0;
}

static void	show_names_n_values(void)
{
	t_var	*anchor;

	anchor = g_ms->env_var;
	while (anchor)
	{
		printf("declare -x %s=\"%s\"\n", anchor->key, anchor->value);
		anchor = anchor->next;
	}
}
