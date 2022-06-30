#include "minishell.h"

void    echo(char **args)
{
	int is_there_nl;
	int i;

	is_there_nl = 1;
	i = 1;
	if (args[i] && ft_strncmp(args[i], "-n", -1) == 0)
	{
		is_there_nl = 0;
		i += 1;
	}
	while (args && args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		++i;
	}
	if (is_there_nl)
		printf("\n");
	// g_ms.exit_code = 0;
}
