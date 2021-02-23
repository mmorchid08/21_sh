/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:23:55 by mmorchid          #+#    #+#             */
/*   Updated: 2019/05/18 00:00:30 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	unsigned char	*toto;
	size_t			i;

	str1 = (unsigned char*)dst;
	str2 = (unsigned char*)src;
	i = 0;
	if (!(toto = (unsigned char*)malloc(sizeof(char) * len)))
		return (NULL);
	if (str1 != NULL || str2 != NULL)
	{
		while (i < len)
		{
			toto[i] = str2[i];
			i++;
		}
		i = 0;
		while (i < len)
		{
			str1[i] = toto[i];
			i++;
		}
	}
	return (dst);
}
