/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 21:07:18 by mmorchid          #+#    #+#             */
/*   Updated: 2019/05/11 23:46:22 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str;
	unsigned char	*src;
	int				i;

	str = (unsigned char*)s1;
	src = (unsigned char*)s2;
	i = 0;
	if (src[i] == '\0')
		return (str[i]);
	while (src[i] != '\0' || str[i] != '\0')
	{
		if (str[i] != src[i])
			return (str[i] - src[i]);
		i++;
	}
	return (0);
}
