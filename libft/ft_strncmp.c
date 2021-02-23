/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 23:12:57 by mmorchid          #+#    #+#             */
/*   Updated: 2019/05/12 00:05:09 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*src;
	size_t			i;

	str = (unsigned char*)s1;
	src = (unsigned char*)s2;
	i = 0;
	while ((src[i] != '\0' || str[i] != '\0') && i < n)
	{
		if (str[i] != src[i])
			return (str[i] - src[i]);
		i++;
	}
	return (0);
}
