/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:51:09 by hmigl             #+#    #+#             */
/*   Updated: 2022/08/12 08:51:46 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_echo(char **argv)
{
	int	is_there_nl;
	int	i;

	is_there_nl = 1;
	i = 1;
	if (argv[i] && ft_strncmp(argv[i], "-n", -1) == 0)
	{
		is_there_nl = 0;
		i += 1;
	}
	while (argv && argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1] && argv[i][0])
			printf(" ");
		++i;
	}
	if (is_there_nl)
		printf("\n");
	g_ms->exit_code = 0;
}
