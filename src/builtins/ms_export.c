#include "minishell.h"

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

static	int	is_a_valid_identifier(char *statement)
{
	int	i;
	int	ignore;

	i = 0;
	ignore = 1;
	while (statement[i] != '\0')
	{
		if (statement[i] == '=')
		{
			ignore = 0;
			break ;
		}
		i++;
	}
	if (ignore)
		return (0);
	i = 0;
	while (statement[i] != '\0')
	{
		if (statement[i] == '=')
			return (!ft_isspace(statement[i - 1]));
		++i;
	}
	return (1);
}

static void	show_invalid_identifier_err(char *invalid_statement)
{
	int		value_len;
	char	*err;

	value_len = ft_strlen(invalid_statement);
	err = ft_substr(invalid_statement, 0, value_len);
	ms_display_error("export: ", ft_strjoin(err, ": not a valid identifier"),
		0);
	free(err);
	g_ms->exit_code = 1;
}

void	ms_export(char **argv)
{
	int		i;
	char	*key;
	char	*value;
	char	**splited;

	if (!argv)
	{
		show_names_n_values();
		g_ms->exit_code = 0;
		return ;
	}
	i = 0;
	while (argv[++i] != NULL)
	{
		if (argv[i][0] == '=')
			show_invalid_identifier_err(argv[i]);
		else if (is_a_valid_identifier(argv[i]))
		{
			splited = ft_split(argv[i], '=');
			key = splited[0];
			value = splited[1];
			add_vars_to_env(key, value, g_ms->env_var);
			g_ms->exit_code = 0;
		}
	}
}
