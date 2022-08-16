/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:21:45 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 18:03:11 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_have_a_var_to_save(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '=' && str[i] != '\"' && str[i] != '\'')
	{
		while (str[++i] && str[i] != '\"' && str[i] != '\'')
		{
			if (str[i] == '=')
				return (1);
		}
	}
	return (0);
}

static int	ft_is_local_var(char **cmd)
{
	int	i;
	int	is_var;
	int	total_vars;

	total_vars = 0;
	i = 0;
	is_var = ft_have_a_var_to_save (cmd[i]);
	if (!is_var)
		return (-1);
	total_vars++;
	while (is_var && cmd[i++])
	{
		if (!is_var && total_vars > 0)
			return (1);
		if (is_var)
			total_vars++;
		is_var = ft_have_a_var_to_save (cmd[i]);
	}
	if (!is_var && cmd[i])
		return (1);
	return (0);
}

static void	ft_save_var_in_correct_struct(char **argv, int has_only_var)
{
	int		i;
	char	**sp;

	i = -1;
	while (ft_have_a_var_to_save(argv[++i]))
	{
		ft_convert_chars (argv[i], '=');
		sp = ft_split(argv[i], 127);
		ft_re_convert_chars (argv[i], '=');
		sp[1] = ft_remove_quote_from_str (sp[1]);
		if (has_only_var)
			g_ms->env_var = add_vars_to_env(sp[0], sp[1], g_ms->env_var);
		else
			g_ms->local_var = add_vars_to_env(sp[0], sp[1], g_ms->local_var);
		ft_free_double_pointer (sp);
	}
}

char	**ft_save_env_vars(t_cmd *cmd)
{
	int		vars;
	char	**rtn;

	if (!cmd->argv)
		return (NULL);
	vars = ft_is_local_var(cmd->argv);
	if (vars == -1)
		return (cmd->argv);
	else if (vars > 0 || g_ms->n_pipe)
		ft_save_var_in_correct_struct (cmd->argv, 0);
	else
		ft_save_var_in_correct_struct (cmd->argv, 1);
	rtn = ft_remove_var_atrib_and_equals (cmd->argv);
	ft_free_double_pointer (cmd->argv);
	return (rtn);
}
