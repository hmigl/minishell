#include "minishell.h"

static int ft_check_out (char *str)
{
	int i;
	int n_redirect;

	i = 0;
	n_redirect = 1;

	while (str[++i] && n_redirect < 3)
	{
		if (str[i] == '>')
			n_redirect++;
		else if(str[i] == '<')
			return (-1);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i+= ft_next_occurrence (&str[i], str[i]);
			return (i);
		}
		else if (str[i] == '|')
			return (-1);
		else if (str[i] >= 33 && str[i] <= 126 )
			return(i + 1);
	}
	return (-1);
}

static int ft_check_in (char *str)
{
	int i;
	int n_redirect;

	i = 0;
	n_redirect = 1;

	while (str[++i] && n_redirect < 3)
	{
		if (str[i] == '<')
			n_redirect++;
		else if(str[i] == '>')
			return (-1);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i+= ft_next_occurrence (&str[i], str[i]);
			return (i);
		}
		else if (str[i] == '|')
			return (-1);
		else if (str[i] >= 33 && str[i] <= 126 )
			return(i + 1);
	}
	return (-1);
}
static int ft_check_after_pipe (char *str)
{
	int i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			return (-1);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			i+= ft_next_occurrence (&str[i], str[i]);
			return (i);
		}
		else if (str[i] >= 33 && str[i] <= 126)
			return(i + 1);
	}
	return (-1);
}
static int	ft_check_after_redirect(char *str, char redirect)
{
	if (redirect == '>')
		return (ft_check_out (str));
	else
		return (ft_check_in (str));
}

int	ft_check_syntax(char *prompt_line)
{
	int i;
	int error;
	i = -1;

	while (prompt_line[++i])
	{
		if (prompt_line[i] == '\'' || prompt_line[i] == '\"' )
			i += ft_next_occurrence (&prompt_line[i], prompt_line[i]);
		else if (prompt_line[i] == '\\')
		{
			printf ("error \\\n"); // ms_display_error()
			g_ms->exit_code = 2;
			return (1);
		}
		else if (prompt_line[i] == '|')
		{
			error = ft_check_after_pipe (&prompt_line[i]);
			if (error == -1)
			{
				printf ("error redirect\n");
				g_ms->exit_code = 2;
				return (1);
			}
			i += error;
		}
		else if (prompt_line[i] == '>' || prompt_line[i] == '<')
		{
			error = ft_check_after_redirect (&prompt_line[i], prompt_line[i]);
			if (error == -1)
			{
				printf ("error redirect\n");
				g_ms->exit_code = 2;
				return (1);
			}
			i += error;
		}
	}
	return (0);
}
