#include "minishell.h"

void	*ft_free_double_pointer (char **pointer)
{
	int i;

	i = 0;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free (pointer);
	return (NULL);
}
