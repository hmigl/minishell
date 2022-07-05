#include "minishell.h"

static void	act_according_to_status(int status, char *dir);
static void	update_pwd(char *oldpwd);
static void	cd_failed(char *dir);

void	ms_cd(char **argv)
{
	char	*dir;
	char	*oldpwd;
	int		operation_status;

	operation_status = 0;
	oldpwd = getcwd(NULL, 0);
	if (argv[2] != NULL)
	{
		ms_display_error("cd: ", "too many arguments", 0);
		g_ms->exit_code = 1;
		return ;
	}
	else if (argv[1] == NULL || !ft_strncmp(argv[1], "~", -1))
	{
		operation_status = -1;
		// get HOME value -> if set then chdir -> status = chdir -> free afterwards
	}
	else
		operation_status = chdir(argv[1]);
	act_according_to_status(operation_status, argv[1]);
	update_pwd(ft_strdup(oldpwd));
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
	if (dir == NULL)
		ms_display_error("cd: ", "HOME not set", 0);
	else
		ms_display_error("cd: ", ft_strjoin(dir,
				": No such file or directory"), 0);
}

static void	update_pwd(char *oldpwd)
{
	ms_unset("PWD");
	ms_unset("OLDPWD");
	// ft_insert_nodes_in_struct(ft_strdup("OLDPWD"), oldpwd);
	// ft_insert_nodes_in_struct(ft_strdup("PWD"), ft_strdup(getcwd(NULL, 0)));
}
