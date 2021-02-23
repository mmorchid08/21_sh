/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:45:14 by mmorchid          #+#    #+#             */
/*   Updated: 2020/01/02 12:33:45 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *s, char c)
{
	int len;
	int count;
	int i;

	len = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			len = 0;
		else if (++len == 1)
			count++;
		i++;
	}
	return (count);
}

static char		*ft_line(const char *s, int *i, char c)
{
	int		h;
	char	*str;

	h = 0;
	while (s[*i] != c && s[*i] != '\0')
	{
		h++;
		(*i)++;
	}
	str = malloc(sizeof(char*) * h);
	*i = *i - h;
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**tab;
	int		k;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (!(tab = (char**)malloc(sizeof(char*) * (ft_count_words(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		tab[j] = ft_line(s, &i, c);
		k = 0;
		while (s[i] != c && s[i])
			tab[j][k++] = s[i++];
		tab[j++][k] = '\0';
	}
	tab[j] = NULL;
	return (tab);
}
