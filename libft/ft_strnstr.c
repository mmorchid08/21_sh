/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:53:59 by mmorchid          #+#    #+#             */
/*   Updated: 2019/05/16 21:56:42 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	char	*src;
	int		i;
	int		j;
	int		k;

	str = (char *)haystack;
	src = (char *)needle;
	k = (int)len;
	i = 0;
	j = 0;
	if (src[j] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (src[j] == str[i + j] && i + j < k)
		{
			j++;
			if (src[j] == '\0')
				return (str + i);
		}
		i++;
	}
	return (NULL);
}
