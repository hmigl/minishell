#include "minishell.h"
static char **ft_alloc_memory (char **split, char **argv)
{
	int alloc;
	int i;

	i = 0;
	alloc = 0;
	while (ft_have_a_var_to_save(argv[i]))
		i++;
	while (argv[alloc])
		alloc++;
	split = ft_calloc (alloc + 1- i, sizeof(char));
	return (split);

}


char **ft_remove_var_atrib_and_equals (char **argv)
{
	char **rtn;
	int i;
	int j;

	i = 0;
	j = 0;
	rtn = ft_alloc_memory (rtn, argv);
	while (ft_have_a_var_to_save(argv[i]))
		i++;
	while (argv[i])
		rtn[j++] = ft_strdup (argv[i++]);
	rtn[j] = 0;
	return (rtn);
}
