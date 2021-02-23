/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 00:16:22 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/19 17:56:44 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned char	*s;
	int				i;
	int				res;
	int				sign;

	sign = 1;
	s = (unsigned char*)str;
	i = 0;
	res = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' ||
			s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
		i++;
	if (s[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	else if (s[i] == '+')
	{
		sign = sign * 1;
		i++;
	}
	while (s[i] != '\0' && s[i] >= '0' && s[i] <= '9')
		res = res * 10 + (s[i++] - '0');
	return (sign * res);
}