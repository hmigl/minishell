/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 09:03:51 by hmigl             #+#    #+#             */
/*   Updated: 2022/08/15 09:43:56 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	welcome(void)
{
	int		fd;
	char	*line;

	fd = open("./src/utils/welcome", O_RDONLY);
	if (fd == -1)
		return ;
	while (1)
	{
		line = get_next_line(fd);
		if (line != NULL)
			printf("%s", line);
		else
			break ;
		ft_free(line);
	}
	close(fd);
}
