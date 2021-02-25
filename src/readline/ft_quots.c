/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 21:26:49 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 21:26:57 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_manage_quots_c1(char **copy, char **str, char *c, int *j)
{
	(*c == 39) ? ft_putstr("quote> ") : ft_putstr("dquote> ");
	g_env.prompt_len = ft_strlen((*c == 39) ? "quote> " : "dquote> ");
	*str = ft_readline();
	*copy = ft_free_strjoin(*copy,
	ft_free_strjoin(ft_strdup("\n"), ft_strdup(*str)));
	*j = 0;
	while ((*str)[*j] && (*str)[*j] != *c)
	{
		ft_encode_char(*str + *j, *c);
		(*j)++;
	}
}

void	ft_manage_quots_c2(char **line, char **copy, char c, int *i)
{
	char	*str;
	int		j;

	g_env.inside_prompt = 1;
	while (g_env.inside_prompt == 1)
	{
		ft_manage_quots_c1(copy, &str, &c, &j);
		if (str && str[j] == c)
		{
			str[j] = '\0';
			*i = ft_strlen((*line)) + j;
			str = ft_free_strjoin(str, ft_strdup(str + j + 1));
			(*line) = ft_free_strjoin((*line),
			ft_free_strjoin(ft_strdup("\n"), str));
			break ;
		}
		else
			(*line) = ft_free_strjoin((*line),
			ft_free_strjoin(ft_strdup("\n"), str));
	}
	(g_env.inside_prompt == 1) && (g_env.inside_prompt = 0);
}

void	ft_manage_quots_c3(char **line, char *c, int *i, int *j)
{
	*c = (*line)[*i];
	(*line)[*i] = '\0';
	(*line) = ft_free_strjoin((*line),
	ft_strdup((*line) + *i + 1));
	*j = *i;
	while ((*line)[*j] && (*line)[*j] != *c)
	{
		ft_encode_char((*line) + *j, *c);
		(*j)++;
	}
}

void	ft_manage_quots(char **line, char **copy)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	*copy = ft_strdup(*line);
	while ((*line) && (*line)[++i])
		if ((*line)[i] == 39 || (*line)[i] == 34)
		{
			ft_manage_quots_c3(line, &c, &i, &j);
			if ((*line)[j] == c && !((*line)[j] = '\0'))
			{
				(*line) = ft_free_strjoin((*line), ft_strdup((*line) + j + 1));
				if (!(*line)[(i = j)])
					return ;
			}
			else
				ft_manage_quots_c2(line, copy, c, &i);
		}
		else if ((*line)[i] == '\\' && (*line)[i + 1] == ' ')
		{
			(*line)[i] = '\0';
			(*line)[i + 1] = -1;
			(*line) = ft_free_strjoin((*line), ft_strdup((*line) + i + 1));
		}
}
