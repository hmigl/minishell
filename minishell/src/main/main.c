#include "minishell.h"


//lembrar de colocar uma checagem de syntax de >> junto com a checagem de quote
int main (int argc, char **argv, char **env )
{
	//ft_start_global_variable();
	g_global = ft_calloc (sizeof (t_minishell), 1);
	g_global->env_var = ft_calloc (sizeof (t_var), 1);
	g_global->env_var->key = ft_calloc (sizeof (char), 1);
	g_global->env_var->value = ft_calloc (sizeof (char), 1);
	ft_save_local_env (env);
	ft_start_shell ();
	// int i = -1;
	// while (env[++i])
	// printf ("%s \n", env[i]);
	// printf ("-----------------------");
	// while (g_global->env_var)
	// {
	// 	printf ("%s %s\n", g_global->env_var->key, g_global->env_var->value);
	// 	g_global->env_var = g_global->env_var->next;
	// }
}
