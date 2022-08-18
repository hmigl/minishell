/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:51:08 by hmigl             #+#    #+#             */
/*   Updated: 2022/08/18 10:44:14 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	act_according_to_status(int status, char *dir);
static void	update_pwd(char *oldpwd);
static void	cd_failed(char *dir);
static void	handle_home(int *operation_status);

void	ms_cd(char **argv)
{
	char	*oldpwd;
	int		operation_status;

	operation_status = 0;
	oldpwd = getcwd(NULL, 0);
	if (argv[1] != NULL && argv[2] != NULL)
	{
		ms_display_error("cd: ", "too many arguments", 0);
		g_ms->exit_code = 1;
		free(oldpwd);
		return ;
	}
	else if (argv[1] == NULL || !ft_strncmp(argv[1], "~", -1))
		handle_home(&operation_status);
	else
		operation_status = chdir(argv[1]);
	act_according_to_status(operation_status, argv[1]);
	update_pwd(oldpwd);
	free(oldpwd);
}

static void	handle_home(int *operation_status)
{
	char	*home1;
	char	*home2;
	char	*hold_home_value;

	home1 = ft_strdup("$HOME");
	home2 = ft_strdup("$HOME");
	*operation_status = -1;
	hold_home_value = ft_find(home1, home2);
	if (hold_home_value[0])
		*operation_status = chdir(hold_home_value);
	free(hold_home_value);
	free(home1);
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
	char	*buffer;

	if (dir == NULL)
		ms_display_error("cd: ", "HOME not set", 0);
	else
	{
		buffer = ft_strjoin(dir, ": No such file or directory");
		ms_display_error("cd: ", buffer, 0);
		free(buffer);
	}
}

static void	update_pwd(char *oldpwd)
{
	char	*old_pwd;
	char	*pwd;
	char	*get_cwd;

	old_pwd = ft_strdup("OLDPWD");
	pwd = ft_strdup("PWD");
	get_cwd = getcwd(NULL, 0);
	g_ms->env_var = add_vars_to_env(old_pwd, oldpwd, g_ms->env_var);
	g_ms->env_var = add_vars_to_env(pwd, get_cwd, g_ms->env_var);
	free(old_pwd);
	free(pwd);
	free(get_cwd);
}
