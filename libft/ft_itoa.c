/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:59:59 by mmorchid          #+#    #+#             */
/*   Updated: 2019/05/13 15:36:33 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_lenint(int n)
{
	int count;

	count = 1;
	if (n < 0)
		count++;
	while (n != 0)
	{
		if (n / 10 != 0)
			count++;
		n = n / 10;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		res;
	int		count;

	res = 0;
	count = ft_lenint(n);
	str = ft_strnew(count);
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n / 10 != 0)
	{
		res = n % 10;
		str[--count] = res + 48;
		n /= 10;
	}
	str[--count] = n % 10 + 48;
	return (str);
}
