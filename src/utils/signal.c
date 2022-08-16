/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:12:19 by phiolive          #+#    #+#             */
/*   Updated: 2022/08/16 19:12:19 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_new_prompt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_ms->exit_code = 130;
}

static void	intr_sig(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	g_ms->exit_code = 128 + sig;
}

static void	quit_sig(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	g_ms->exit_code = 131;
}

void	stdin_sig(void)
{
	signal(SIGINT, display_new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	exec_sig(void)
{
	signal(SIGINT, intr_sig);
	signal(SIGQUIT, quit_sig);
}
