/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:26:20 by hmigl             #+#    #+#             */
/*   Updated: 2022/07/21 20:16:57 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*new;
	size_t	j;
	size_t	i;

	new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1 * sizeof(char));
	if (!new)
	{
		free(new);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		++i;
	}
	j = -1;
	if (s2)
	{
		while (s2[++j])
			new[i + j] = s2[j];
	}
	new[i + j] = '\0';
	return (new);
}
