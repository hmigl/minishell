#include "minishell.h"

static int	setup_n(char *argv);
static int	is_invalid_arg(char *n);

void	ms_exit(char **argv)
{
	printf("exit\n");
	if (argv[2] != NULL)
	{
		ms_display_error("exit: ", "too many arguments", 0);
		g_ms->exit_code = 1;
		return ;
	}
	if (argv[1])
	{
		//ms_global_cleanup();
		exit(setup_n(argv[1]));
	}
	exit(g_ms->exit_code);
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
