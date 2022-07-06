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
		if (argv[i + 1])
			printf(" ");
		++i;
	}
	if (is_there_nl)
		printf("\n");
	g_ms->exit_code = 0;
}
