#include "minishell.h"

static void ft_trim_redirect_cpy (char *str, char *rtn)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' )
		rtn[j++] = str[i++];
	while (str[i] == '<' || str[i] == '>' )
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\"' || str[i] == '\'')
		i += ft_next_occurrence (&str[i], str[i]);
	else
	{
		while (str[i] != ' ' && str[i])
			i++;
	}
	while (str[i])
		rtn[j++] = str[i++];
	free (str);
	str = NULL;
}

char *ft_trim_redirect (char *str)
{
	int i;
	char *rtn;
	int trim;

	trim = 0;
	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' )
		i++;
	while (str[i + trim] == '<' || str[i + trim] == '>' )
		trim++;
	while (str[i + trim] == ' ')
		trim++;
	if (str[i + trim] == '\"' || str[i + trim] == '\'')
		trim += ft_next_occurrence (&str[i + trim], str[i + trim]);
	else
	{
		while (str[i + trim] != ' ' && str[i + trim])
			trim++;
	}
	rtn = ft_calloc (ft_strlen(str) - trim + 1, sizeof(char));
	ft_trim_redirect_cpy (str, rtn);
	return (rtn);
}

static char *ft_get_file_name (char *prompt_line, char quote)
{
	char *file_name;
	int i;

	i = 0;
	if (quote)
	{
		while (prompt_line[i] != quote)
			i++;
	}
	else
	{
		while (prompt_line[i] != ' ' && prompt_line[i])
			i++;
	}
	file_name = ft_calloc (i + 1, sizeof(char));
	ft_strlcpy (file_name, prompt_line, i + 1);
	return (file_name);
}

char *ft_file_name (char *prompt_line, char redirect)
{
	char *file_name;
	int	i;

	i = 0;
	while (prompt_line[i] == redirect)
		i++;
	while (prompt_line[i] == ' ')
		i++;
	if (prompt_line[i] == '\"' || prompt_line[i] == '\'')
		file_name = ft_get_file_name (&prompt_line[i + 1], prompt_line[i]);
	else
		file_name = ft_get_file_name (&prompt_line[i], 0);
	return (file_name);
}

static char* ft_check_redirect_type (char *str, char *prompt_line, char redirect)
{
	if (redirect == '>')
		str = ft_out_redirect (str, prompt_line);
	else
		str = ft_in_redirect (str, prompt_line);
	return (str) ;

}
//colocar checagem em ponto específico fora do redirect (checar quote, checar numero de redirect e checar backslash checar &)
char *ft_redirect (char *prompt_line)
{
	int i;

	i = -1;
	while (prompt_line[++i])
	{
		if (prompt_line[i] == '\'' || prompt_line[i] == '\"')
			i += (ft_next_occurrence (&prompt_line[i], prompt_line[i]));
		else if (prompt_line[i] == '>' || prompt_line[i] == '<')
		{
			prompt_line = ft_check_redirect_type (prompt_line , &prompt_line[i], prompt_line[i]);
			i = -1;
			if (g_ms->redirect_error)
				break;
		}
	}
	return (prompt_line);
}
