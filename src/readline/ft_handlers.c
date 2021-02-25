/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:58:39 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:58:41 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static int		ft_strsplit_tab_alloc(const char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[j] && str[j] == c && (j == 0 || str[j - 1] != '\\'))
		j++;
	while (str[j])
	{
		if (str[j] && str[j] == c && (j == 0 || str[j - 1] != '\\'))
		{
			while (str[j])
				if (str[j] == c && (j == 0 || str[j - 1] != '\\'))
					j++;
				else
					break ;
			if (str[j])
				i++;
		}
		j++;
	}
	return (i);
}

static char		*ft_strsplit_word_alloc(const char *str, int *start, int end)
{
	char	*tabc;
	int		i;

	i = 0;
	tabc = (char *)malloc(sizeof(char) * ((end - *start) + 1));
	if (!tabc)
		exit(1);
	while (*start < end)
	{
		tabc[i] = str[*start];
		i++;
		(*start)++;
	}
	tabc[i] = '\0';
	return (tabc);
}

char			**ft_escape_strsplit(char const *s, char c)
{
	char	**tabc;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	tabc = (char**)malloc(sizeof(char *) *
	(ft_strsplit_tab_alloc(s, c) + 2));
	if (!tabc)
		exit(1);
	while (s[i])
	{
		j = i;
		while (s[j] && !(s[j] == c && (j == 0 || s[j - 1] != '\\')))
			j++;
		if (j > i)
			tabc[k++] = ft_strsplit_word_alloc(s, &i, j);
		else
			i++;
	}
	tabc[k] = 0;
	return (tabc);
}

char			*ft_free_strjoin(char *str1, char *str2)
{
	char *str;

	if (!str1 || !str2)
		exit(1);
	if (!(str = ft_strjoin(str1, str2)))
		exit(1);
	free(str1);
	free(str2);
	return (str);
}

void			ft_get_cursor_coor(int *x, int *y)
{
	char	buf[11];
	char	*tmp;

	ft_bzero(buf, 11);
	ft_putstr("\033[6n");
	read(0, buf, 10);
	*y = ft_atoi(buf + 2);
	if ((tmp = ft_strchr(buf, ';')))
		*x = ft_atoi(tmp + 1);
	else
		*x = 0;
}
