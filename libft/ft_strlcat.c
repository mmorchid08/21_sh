/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 20:26:05 by mmorchid          #+#    #+#             */
/*   Updated: 2019/05/13 13:05:58 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	a;
	size_t	b;
	size_t	j;

	i = 0;
	a = ft_strlen(dst);
	b = ft_strlen(src);
	if (size <= a)
		return (size + b);
	while (dst[i] != '\0' && i < size - 1)
		i++;
	j = 0;
	while (src[j] != '\0' && j < size - 1 && i < size - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (a + b);
}
