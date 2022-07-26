#include "minishell.h"

// static void	heredoc_intr_sig(int sig)
// {
// 	(void)sig;
// 	g_ms->exit_code = 130;
// 	ft_putstr_fd("\n", 1);
// 	exit(130);
// }

static void	heredoc_intr_sig(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_ms->exit_code = 130;
}

void	heredoc_stdin_sig(void)
{
	signal(SIGINT, heredoc_intr_sig);
	signal(SIGQUIT, SIG_IGN);
}
