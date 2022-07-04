#include "minishell.h"

static char *ft_convert (char *content, char *key, char *command)
{
	int i;
	int k;
	int c;
	char *convert;

	k = -1;
	i = -1;
	c = -1;
	convert = ft_calloc (ft_strlen(command) + ft_strlen(content) - ft_strlen(key) , sizeof(char));
	while (command[++i])
	{
		if (command[i] == '$')
		{
			while (content[++k])
				convert[++c] = content[k];
			i++;
			while (command[i] && command[i] != ' ' && command[i] != '\'' && command[i] != '\"' && command[i] != '$')
				i++;
			break;
		}
		else
			convert[++c] = command[i];
	}
	while (command[i])
		convert[++c] = command[i++];
	free (command);
	return (convert);
}

static char *ft_cannot_find (char *variable, char *command)
{
	int i;
	int k;
	char *convert;

	k = -1;
	i = 1;
	while (variable[i] && variable[i] != ' ' && variable[i] != '\'' && variable[i] != '\"' && variable[i] != '$')
		i++;
	convert = ft_calloc (ft_strlen(command) - i + 1, sizeof(char));
	i = 0;
	while (command[++k] != '$' && command[k])
		convert[i++] = command[k];
	k++;
	while (command[k] && command[k] != ' ' && command[k] != '\'' && command[k] != '\"' && command[k] != '$')
		k++;
	while (command[k])
		convert[i++] = command[k++];
	free (command);
	return (convert);
}

static char *ft_find (char *variable, char *command)
{
	int i;
	int bigger;
	t_var *anchor;

	anchor = g_ms->env_var;
	i = 1;
	while (variable[i] && variable[i] != ' ' && variable[i] != '\'' && variable[i] != '\"' && variable[i] != '$')
		i++;
	while (anchor)
	{
		bigger = i - 1;
		if (ft_strlen(anchor->key) > i -1)
			bigger = ft_strlen(anchor->key);
		if (!(ft_strncmp (anchor->key, &variable[1], bigger)))
			return (ft_convert(anchor->value, anchor->key, command));
		else
			anchor = anchor->next;
	}
	return (ft_cannot_find (variable, command));
}

char *ft_expand_env_var (char *cmd)
{
 	int i;
	int trigger = 0;

	i = -1;
 	while (cmd[++i])
	{
		if (cmd[i] == '\"')
			trigger = 1;
		else if (cmd[i] == '\'' && !trigger)
			i += ft_next_occurrence (&cmd[i], '\'');
		else if (cmd[i] == '$' && cmd[i + 1] != ' ' && cmd[i + 1])
		{
			cmd = ft_find(&cmd[i], cmd);
			i = -1;
		}
	}
	return (cmd);
}
