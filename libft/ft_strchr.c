/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 23:23:51 by mmorchid          #+#    #+#             */
/*   Updated: 2019/05/11 23:35:10 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char*)s;
	i = 0;
	while (str[i] != '\0' || c == '\0')
	{
		if (str[i] == c)
			return ((char*)s + i);
		i++;
	}
	return (NULL);
}
