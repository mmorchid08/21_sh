/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:49:21 by youarzaz          #+#    #+#             */
/*   Updated: 2019/03/30 21:32:14 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *tmp;

	if (s1 && s2)
	{
		tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (tmp)
		{
			tmp = ft_strcpy(tmp, s1);
			tmp = ft_strcat(tmp, s2);
			return (tmp);
		}
	}
	return (NULL);
}

char	*ft_strjoin_free(char const *s1, char const *s2, int i)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (i == 1)
		ft_strdel((char **)&s1);
	if (i == 2)
		ft_strdel((char **)&s2);
	if (i == 3)
	{
		ft_strdel((char **)&s1);
		ft_strdel((char **)&s2);
	}
	return (str);
}
