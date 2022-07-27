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


// preciso colocar os erros dentro da estrutura e parar de executar os comandos caso tenha erro de permissão !
// integrar heredoc
// TESTES
// as <1212 (fica em loop infinito, checar)
// parse de apenas redirect da segfault
