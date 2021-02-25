/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:08:57 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 19:09:05 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_move_home(char *line, int start)
{
	int len;

	len = g_env.cur_all_col;
	if (line)
	{
		if (start)
			while (line && len-- >= 0)
				ft_move_left(line, start);
		else
		{
			if (len > 0 && line[len - 1] == '\n')
			{
				ft_move_left(line, 1);
				len--;
			}
			while (line && len-- > 0 && line[len] != '\n')
				ft_move_left(line, 1);
		}
	}
}

void	ft_move_end(char *line, int start)
{
	int len;

	if (line)
	{
		len = ft_strlen(line);
		if (start)
		{
			while (g_env.cur_all_col < len)
				ft_move_right(line, start);
		}
		else
		{
			if (g_env.cur_all_col < len && line[g_env.cur_all_col] == '\n')
				ft_move_right(line, 1);
			while (g_env.cur_all_col < len && line[g_env.cur_all_col] != '\n')
				ft_move_right(line, 1);
		}
	}
}

void	ft_move_up(char **line)
{
	int		i;

	if (g_env.his && !(g_env.his->prev) && !g_env.his->type)
		ft_save_his((!(*line)) ? ft_strdup("") : ft_strdup(*line), 1);
	if ((*line) && g_env.his)
	{
		free(g_env.his->dis_line);
		g_env.his->dis_line = ft_strdup((*line));
	}
	if (g_env.his && !g_env.his->prev)
		g_env.his->cur = g_env.cur_all_col;
	if (g_env.his && g_env.his->next)
	{
		ft_move_home((*line), 1);
		ft_putstr(tgetstr("cd", NULL));
		ft_strdel(line);
		i = -1;
		while (g_env.his->next->dis_line && (g_env.his->next->dis_line)[++i])
			ft_putstr_char((g_env.his->next->dis_line)[i], line);
		g_env.his = g_env.his->next;
	}
}
