#include "minishell.h"

void    exec_builtin(t_cmd *cmd)
{
    if (cmd->argv == NULL)
        return ;
    if (!(ft_strncmp(cmd->argv[0], "pwd", -1)))
		pwd();
	if (!(ft_strncmp(cmd->argv[0], "echo", -1)))
        echo(cmd->argv);
    if (!(ft_strncmp(cmd->argv[0], "env", -1)))
		env();
}
