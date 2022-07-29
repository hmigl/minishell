#include "minishell.h"

static char	*ft_convert(char *content, char *key, char *cmd)
{
	int		i;
	int		k;
	int		c;
	char	*convert;
	size_t	aux;

	i = -1;
	k = -1;
	c = -1;
	aux = ft_strlen(cmd) + ft_strlen(content) - ft_strlen(key);
	convert = ft_calloc(aux, sizeof(char));
	while (cmd[++i])
	{
		if (cmd[i] == '$')
		{
			while (content[++k])
				convert[++c] = content[k];
			i++;
			while (cmd[i] && is_not_spc_quote_dollar(cmd[i]))
				i++;
			break ;
		}
		else
			convert[++c] = cmd[i];
	}
	while (cmd[i])
		convert[++c] = cmd[i++];
	free(cmd);
	return (convert);
}


char *ft_expand_exit_error (char *cmd)
{
	char *key;
	char *value;
	char *rtn;

	key = ft_strdup ("?");
	value = ft_itoa (g_ms->exit_code);
	rtn = ft_convert(value, key, cmd);
	ft_free(key);
	ft_free(value);
	return (rtn);
}

static char	*ft_cannot_find(char *var, char *cmd)
{
	int		i;
	int		k;
	char	*convert;

	k = -1;
	i = 1;
	while (var[i] && is_not_spc_quote_dollar(var[i]))
		i++;
	convert = ft_calloc(ft_strlen(cmd) - i + 1, sizeof(char));
	i = 0;
	while (cmd[++k] != '$' && cmd[k])
		convert[i++] = cmd[k];
	k++;
	while (cmd[k] && is_not_spc_quote_dollar(cmd[k]))
		k++;
	while (cmd[k])
		convert[i++] = cmd[k++];
	free(cmd);
	return (convert);
}

char	*ft_find(char *var, char *cmd)
{
	size_t	i;
	int		bigger;
	t_var	*anchor;

	anchor = g_ms->env_var;
	i = 1;
	if (var[i] == '?')
		return (ft_expand_exit_error (cmd));
	while (var[i] && is_not_spc_quote_dollar(var[i]))
		i++;
	while (anchor)
	{
		bigger = i - 1;
		if (ft_strlen(anchor->key) > i -1)
			bigger = ft_strlen(anchor->key);
		if (!(ft_strncmp(anchor->key, &var[1], bigger)))
			return (ft_convert(anchor->value, anchor->key, cmd));
		else
			anchor = anchor->next;
	}
	return (ft_cannot_find(var, cmd));
}

char	*ft_expand_env_var(char *cmd)
{
	int	i;
	int	trigger;

	trigger = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\"')
			trigger = 1;
		else if (cmd[i] == '\'' && !trigger)
			i += ft_next_occurrence(&cmd[i], '\'');
		else if (cmd[i] == '$' && cmd[i + 1] != ' ' && cmd[i + 1])
		{
			cmd = ft_find(&cmd[i], cmd);
			i = -1;
		}
	}
	return (cmd);
}
