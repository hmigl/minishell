#include "minishell.h"

t_minishell	*g_ms;

static void	repl(void)
{
	char	*input;

	while (1)
	{
		stdin_sig();
		g_ms->n_pipe = 0;
		g_ms->n_cmd = 0;
		input = ft_prompt();
		if (ft_check_syntax(input))
		{
			free(input);
			continue ;
		}
		ft_alloc_cmd(input);
		ft_unpipe_and_alloc(input);
		ft_parse();
		ft_process_cmds();
	}
}

static void	ms_prepare(char **env)
{
	g_ms = ft_calloc(1, sizeof(t_minishell)); // check return and exit if NULL
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
