/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:51:09 by hmigl             #+#    #+#             */
/*   Updated: 2022/08/12 08:51:46 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_n(char *argv);
static int	is_invalid_arg(char *n);

void	ms_exit(char **argv)
{
	int	error;
	int	n;

	printf("exit\n");
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
		{
			ms_display_error("exit: ", "too many arguments", 0);
			g_ms->exit_code = 1;
			return ;
		}
	}
	error = g_ms->exit_code;
	rl_clear_history();
	if (argv[1])
	{
		n = setup_n(argv[1]);
		if (n > 255)
			n -= 256;
		free_all_struct(1);
		exit(n);
	}
	free_all_struct(1);
	exit(error);
}

static int	setup_n(char *argv)
{
	int	n;

	if (!is_invalid_arg(argv))
		n = ft_atoi(argv);
	else
	{
		n = 2;
		ms_display_error("exit: ", "numeric argument required", 0);
	}
	return (n);
}

static int	is_invalid_arg(char *n)
{
	int	i;

	i = 0;
	while (n[i])
	{
		if (!ft_isdigit(n[i]))
			return (1);
		++i;
	}
	return (0);
}
