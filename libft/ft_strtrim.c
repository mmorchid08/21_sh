/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 00:30:05 by mmorchid          #+#    #+#             */
/*   Updated: 2019/05/18 02:23:33 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	j = 0;
	if (s)
	{
		k = ft_strlen(s);
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			i++;
		if (s[i] == '\0')
			return (ft_strdup(""));
		k--;
		while (s[k] == ' ' || s[k] == '\n' || s[k] == '\t')
			k--;
		if (!(str = ft_strnew((k - i) + 1)))
			return (NULL);
		while (s[i] != '\0' && i <= k)
			str[j++] = s[i++];
		str[j] = '\0';
		return (str);
	}
	return (0);
}
