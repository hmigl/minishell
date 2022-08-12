/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:51:09 by hmigl             #+#    #+#             */
/*   Updated: 2022/08/12 08:51:46 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(void)
{
	t_var	*anchor;

	anchor = g_ms->env_var;
	while (anchor)
	{
		printf("%s=%s\n", anchor->key, anchor->value);
		anchor = anchor->next;
	}
	g_ms->exit_code = 0;
}
