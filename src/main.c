#include "minishell.h"

t_minishell	*g_ms;

static void	repl(void)
{
	char	*prompt_line;

	while (1)
	{
		stdin_sig();
		g_ms->n_pipe = 0;
		g_ms->n_cmd = 0;
		prompt_line = ft_prompt();
		ft_save_history(prompt_line);
		if (ft_check_syntax(prompt_line))
		{
			free(prompt_line);
			continue ;
		}
		ft_alloc_cmd(prompt_line);
		ft_unpipe_and_alloc(prompt_line);
		ft_parse();
		ft_process_cmds();
		//ft_print_nodes();
	}
}

static void	ms_prepare(char **env)
{
	g_ms = ft_calloc(1, sizeof(t_minishell)); // check return and exit if NULL
	ft_import_env(env);
	ft_save_paths();
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
