/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:03:47 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:38:52 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*ft_alloc_mem(char *rtn, char *argv)
{
	int		i;
	char	trigger;
	int		alloc;

	trigger = 0;
	i = 0;
	alloc = 1;
	while (argv[i])
	{
		if ((argv[i] == '\'' || argv[i] == '\"') && !trigger)
			trigger = argv[i];
		else if (argv[i] == trigger && trigger)
			trigger = 0;
		else
			alloc++;
		i++;
	}
	rtn = ft_calloc (alloc, sizeof(char));
	return (rtn);
}

static	void	ft_copy_argv(char *rtn, char *argv)
{
	int		i;
	char	trigger;
	int		j;

	trigger = 0;
	i = 0;
	j = 0;
	while (argv[i])
	{
		if ((argv[i] == '\'' || argv[i] == '\"') && !trigger)
			trigger = argv[i];
		else if (argv[i] == trigger && trigger)
			trigger = 0;
		else
			rtn[j++] = argv[i];
		i++;
	}
	return ;
}

char	*ft_remove_quote_from_str(char *argv)
{
	char	*rtn;

	rtn = NULL;
	rtn = ft_alloc_mem(rtn, argv);
	ft_copy_argv(rtn, argv);
	free(argv);
	return (rtn);
}

void	ft_remove_quotes_from_cmd_node(t_cmd *cmd)
{
	int	j;

	j = 0;
	if (cmd->argv)
	{
		while (cmd->argv[j])
		{
			cmd->argv[j] = ft_remove_quote_from_str(cmd->argv[j]);
			j++;
		}
	}
	return ;
}
