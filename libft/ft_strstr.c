/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 01:34:46 by mmorchid          #+#    #+#             */
/*   Updated: 2019/04/27 12:13:21 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*str;
	char	*src;
	int		i;
	int		j;

	str = (char *)haystack;
	src = (char *)needle;
	i = 0;
	j = 0;
	if (src[j] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (src[j] == str[i + j])
		{
			j++;
			if (src[j] == '\0')
				return (str + i);
		}
		i++;
	}
	return (NULL);
}
