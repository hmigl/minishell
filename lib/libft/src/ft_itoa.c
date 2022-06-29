/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmigl <hmigl@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:24:03 by hmigl             #+#    #+#             */
/*   Updated: 2022/01/06 11:43:25 by hmigl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_numlen(int num)
{
	if (!(num / 10))
		return (1);
	return (1 + ft_numlen(num / 10));
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	nlen;
	int		sig;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nlen = ft_numlen(n);
	sig = n < 0;
	str = (char *)malloc((sig + nlen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (sig)
	{
		n *= -1;
		str[0] = '-';
	}
	str[sig + nlen] = '\0';
	while (nlen--)
	{
		str[sig + nlen] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
