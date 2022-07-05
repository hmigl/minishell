#include "minishell.h"

t_minishell	*g_ms;
//caramba >1 caramba >2 caraaaaamba <3 carma >1caramba >1 caramba >2 caraaaaamba <3 carma >1
static void	ms_prepare(char **env)
{
	g_ms = ft_calloc (1,sizeof(t_minishell));
	//ft_bzero((void)g_ms, sizeof(t_minishell));
	ft_save_local_env(env);
}

// TODO:
// lembrar de colocar uma checagem de syntax de >> junto
// com a checagem de quotes
//
// remember that argc and argv will probably be unused (validate?)
// checar pipes antes de todos !
// checar redirect = >1 > 2 >3 <1 | >5 >6
int	main(int argc, char *argv[], char *envp[]) // maybe use __environ__
{
	ms_prepare(envp);
	ft_start_shell(); // change to repl() (read, eval, print, loop)
	return (0);
}

