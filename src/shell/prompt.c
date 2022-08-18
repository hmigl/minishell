/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:26:29 by hmigl             #+#    #+#             */
/*   Updated: 2022/08/17 21:38:07 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define YELLOW "\001\033[1;33m\002"
#define GREEN "\001\033[1;32m\002"
#define BLUE "\001\033[1;34m\002"
#define MAGENTA_LIGHT "\001\033[1;95m\002"
#define RESET "\001\033[0;0m\002"

void	ft_alloc_cmd(char *str)
{
	int	i;
	int	alloc_cmd;

	alloc_cmd = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == '|')
			alloc_cmd++;
		i++;
	}
	i = 0;
	g_ms->cmds = ft_calloc(alloc_cmd, sizeof(t_cmd));
	return ;
}

int	ft_save_history(char *prompt_line)
{
	int	i;
	int	only_space;

	i = -1;
	only_space = 1;
	while (prompt_line[++i])
	{
		if (prompt_line[i] != ' ')
		{
			only_space--;
			break ;
		}
	}
	if (!only_space)
	{
		add_history(prompt_line);
		return (1);
	}
	return (0);
}

static char	*getcurdir(void)
{
	char	*cwd;
	char	**cwd_matriz;
	int		i;

	cwd = getcwd(NULL, 0);
	cwd_matriz = ft_split(cwd, '/');
	ft_free(cwd);
	i = 0;
	if (cwd_matriz[i] == NULL)
		cwd = ft_strdup("/");
	else
	{
		while (cwd_matriz[i] != NULL)
		{
			if (cwd_matriz[i + 1] == NULL)
			{
				cwd = ft_strdup(cwd_matriz[i]);
				break ;
			}
			i++;
		}
	}
	ft_free_double_pointer(cwd_matriz);
	return (cwd);
}

static char	*format_prompt(void)
{
	char	*prompt;
	char	*current_dir;
	char	*buffer;
	char	*tmp;

	buffer = ft_strjoin(getenv("USER"), "@minishell ");
	tmp = getcurdir();
	current_dir = ft_strjoin(tmp, "$ ");
	prompt = ft_strjoin(buffer, current_dir);
	ft_free(tmp);
	ft_free(current_dir);
	ft_free(buffer);
	return (prompt);
}

char	*ft_prompt(void)
{
	char	*buffer;
	char	*ms_prompt;

	ms_prompt = format_prompt();
	buffer = readline(ms_prompt);
	free(ms_prompt);
	if (buffer == NULL)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		free_all_struct(1);
		rl_clear_history();
		exit(0);
	}
	if (!ft_save_history(buffer))
	{
		free (buffer);
		return (NULL);
	}
	return (buffer);
}
