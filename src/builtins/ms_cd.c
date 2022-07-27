#include "minishell.h"

static void	act_according_to_status(int status, char *dir);
static void	update_pwd(char *oldpwd);
static void	cd_failed(char *dir);

void	ms_cd(char **argv)
{
	char	*oldpwd;
	char	*hold_home_value;
	int		operation_status;
	char	*home1;
	char	*home2;

	operation_status = 0;
	oldpwd = getcwd(NULL, 0);
	if (argv[1] && argv[2] != NULL)
	{
		ms_display_error("cd: ", "too many arguments", 0);
		g_ms->exit_code = 1;
		free (oldpwd);
		return ;
	}
	else if (argv[1] == NULL || !ft_strncmp(argv[1], "~", -1))
	{
		home1 = ft_strdup("$HOME");
		home2 = ft_strdup("$HOME");
		operation_status = -1;
		hold_home_value = ft_find(home1, home2);
		if (hold_home_value[0])
			operation_status = chdir(hold_home_value);
		free(hold_home_value);
		free (home1);
		free (home2);
	}
	else
		operation_status = chdir(argv[1]);
	act_according_to_status(operation_status, argv[1]);
	update_pwd(oldpwd);
	free (oldpwd);
}

static void	act_according_to_status(int status, char *dir)
{
	if (status < 0)
	{
		cd_failed(dir);
		g_ms->exit_code = 1;
	}
	else
		g_ms->exit_code = 0;
}

static void	cd_failed(char *dir)
{
	char* temp_join;

	temp_join = ft_strjoin(dir, ": No such file or directory");
	if (dir == NULL)
		ms_display_error("cd: ", "HOME not set", 0);
	else
		ms_display_error("cd: ", temp_join, 0);
	free (temp_join);
	return ;
}

static void	update_pwd(char *oldpwd)
{
	char *OLD_PWD;
	char *PWD;
	char *GET_CDW;

	OLD_PWD = ft_strdup("OLDPWD");
	PWD = ft_strdup("PWD");
	GET_CDW = getcwd(NULL, 0);
	g_ms->env_var = add_vars_to_env(OLD_PWD, oldpwd, g_ms->env_var);
	g_ms->env_var = add_vars_to_env(PWD, GET_CDW, g_ms->env_var);
	free (OLD_PWD);
	free (PWD);
	free (GET_CDW);
	return ;
}
