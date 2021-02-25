/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:58:30 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 18:58:39 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_line_down(char **line)
{
	int i;

	if (*line)
	{
		i = g_env.cur_all_col;
		while (i >= 0 && (*line)[i] != '\n')
			i--;
		i = g_env.cur_all_col - i - 1;
		if ((*line) &&
		(*line)[g_env.cur_all_col] == '\n' && i < g_env.cur_mult_col)
			i = g_env.cur_mult_col;
		ft_move_end((*line), 0);
		ft_move_right((*line), 1);
		if (i > g_env.cur_mult_col)
			g_env.cur_mult_col = i;
		while (--i >= 0 && (*line)[g_env.cur_all_col] != '\n')
			ft_move_right((*line), 1);
	}
}

void	ft_line_up(char **line)
{
	int i;

	if (*line)
	{
		i = g_env.cur_all_col;
		if ((*line) && (*line)[i] == '\n')
			i--;
		while ((*line) && i >= 0 && (*line)[i] != '\n')
			i--;
		i = g_env.cur_all_col - i - 1;
		if ((*line) &&
		(*line)[g_env.cur_all_col] == '\n' && i < g_env.cur_mult_col)
			i = g_env.cur_mult_col;
		ft_move_home((*line), 0);
		ft_move_left((*line), 1);
		ft_move_home((*line), 0);
		if (i > g_env.cur_mult_col)
			g_env.cur_mult_col = i;
		while (--i >= 0 && (*line)[g_env.cur_all_col] != '\n')
			ft_move_right((*line), 1);
	}
}

void	ft_word_right(char *line)
{
	int i;

	i = g_env.cur_all_col;
	while (line[i] && (ft_isalnum(line[i])))
	{
		ft_move_right(line, 1);
		i++;
	}
	while (line[i] && !ft_isalnum(line[i]))
	{
		ft_move_right(line, 1);
		i++;
	}
}

void	ft_word_left(char *line)
{
	int i;

	i = g_env.cur_all_col;
	while (i > 0 && !(ft_isalnum(line[i - 1])))
	{
		ft_move_left(line, 1);
		i--;
	}
	while (i > 0 && ft_isalnum(line[i - 1]))
	{
		ft_move_left(line, 1);
		i--;
	}
}

void	ft_move_down(char **line)
{
	int i;

	if ((*line) && g_env.his)
	{
		free(g_env.his->dis_line);
		g_env.his->dis_line = ft_strdup((*line));
	}
	if ((*line) && g_env.his && g_env.his->prev)
	{
		ft_move_home((*line), 1);
		ft_putstr(tgetstr("cd", NULL));
		ft_strdel(line);
		i = -1;
		while (g_env.his->prev->dis_line && (g_env.his->prev->dis_line)[++i])
			ft_putstr_char((g_env.his->prev->dis_line)[i], line);
		g_env.his = g_env.his->prev;
		if (!(g_env.his->prev) && g_env.his->cur >= 0)
		{
			i = ft_strlen(g_env.his->dis_line) - g_env.his->cur;
			while (--i >= 0)
				ft_move_left(g_env.his->dis_line, 1);
		}
	}
}
