#include "minishell.h"

void	ms_display_error(char *id, char *err, int should_quit)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	if (should_quit) {
		// cleanup eveything()
		exit(g_ms->exit_code);
	}
}
