/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symbole.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:36:22 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 22:36:37 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_manage_symbol_c2(char **line, int i)
{
	char *tmp;

	if ((*line)[i] == '$' && (*line)[i + 1] && (*line)[i + 1] == '$')
	{
		(*line)[i] = '\0';
		tmp = ft_strdup((*line) + i + 2);
		(*line) = ft_free_strjoin((*line), ft_itoa(getpid()));
		(*line) = ft_free_strjoin((*line), tmp);
	}
}

void	ft_manage_symbol_c1(char **line, int *i, int j)
{
	char *tmp;
	char *val;

	ft_manage_symbol_c2(line, *i);
	if ((*line)[*i] == '$' && ft_isprint((*line)[*i + 1])
	&& (*line)[*i + 1] != ' ')
	{
		(*line)[*i] = '\0';
		j = (*i) + 1;
		while ((*line)[j] && ft_isalnum((*line)[j]) && (*line)[j] != -1)
			j++;
		tmp = ft_strsub((*line), *i + 1, j - *i - 1);
		val = ft_get_var_value(g_env.var, tmp);
		free(tmp);
		if (val && (*line)[j])
			(*line) = ft_free_strjoin((*line), ft_strjoin(val, (*line) + j));
		else if (val)
			(*line) = ft_free_strjoin((*line), ft_strdup(val));
		else if ((*line)[j])
			(*line) = ft_free_strjoin((*line), ft_strdup((*line) + j));
		(*i)--;
	}
}

void	ft_manage_symbol(char **line)
{
	int		i;
	int		j;
	char	*val;

	i = -1;
	val = NULL;
	while ((*line) && (*line)[++i])
	{
		if ((*line)[(j = i)] == 126 && (i == 0 ||
		(i > 0 && (*line)[i - 1] == ' ')))
		{
			if ((*line)[i + 1] == '\0' ||
			(*line)[i + 1] == ' ' || (*line)[i + 1] == '/')
				val = ft_strdup(g_env.home);
			else if ((*line)[i + 1] != '\0')
				ft_check_users(&val, (*line) + i + 1, &i);
			if (val)
			{
				(*line)[j] = '\0';
				(*line) = ft_free_strjoin((*line),
				ft_free_strjoin(val, ft_strdup((*line) + i + 1)));
			}
		}
		ft_manage_symbol_c1(line, &i, j);
	}
}
