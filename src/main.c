/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:21:04 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 17:21:05 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*g_ms;

static void	repl(void)
{
	char	*input;

	welcome();
	while (1)
	{
		stdin_sig();
		g_ms->n_pipe = 0;
		g_ms->n_cmd = 0;
		g_ms->total_cmd = 0;
		input = ft_prompt();
		if (!input || ft_check_syntax(input))
		{
			if (input)
				free(input);
			continue ;
		}
		ft_alloc_cmd(input);
		ft_unpipe_and_alloc(input);
		g_ms->total_cmd = g_ms->n_pipe + 1;
		ft_parse();
		ft_process_cmds();
	}
}

static void	ms_prepare(char **env)
{
	g_ms = ft_calloc(1, sizeof(t_minishell));
	ft_import_env(env);
	g_ms->exit_code = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc > 1 && argv)
	{
		ft_putendl_fd("usage: ./minishell", STDERR_FILENO);
		return (1);
	}
	ms_prepare(envp);
	repl();
	return (0);
}
