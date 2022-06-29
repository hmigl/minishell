#include "minishell.h"

t_minishell	g_ms;

static void	ms_prepare(char **env)
{
	ft_bzero(&g_ms, sizeof(t_minishell));
	ft_save_local_env(env);
}

// TODO:
// lembrar de colocar uma checagem de syntax de >> junto
// com a checagem de quotes
//
// remember that argc and argv will probably be unused
int	main(int argc, char *argv[], char *env[])
{
	ms_prepare(env);
	ft_start_shell();
}
