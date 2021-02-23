/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 21:40:42 by mmorchid          #+#    #+#             */
/*   Updated: 2019/05/11 23:28:32 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	len;

	str = (char*)s;
	len = ft_strlen(str);
	while (len != 0)
	{
		if (str[len] == c)
			return (str + len);
		len--;
	}
	if (str[len] == c)
		return (str + len);
	return (NULL);
}
