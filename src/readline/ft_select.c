/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:00:53 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 15:00:54 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_toggle_select(char *line)
{
	int i;
	int j;

	if (g_env.select_mode)
	{
		if (g_env.select_pos < g_env.cur_all_col)
		{
			i = g_env.cur_all_col - g_env.select_pos;
			j = i;
			while (i--)
				ft_move_left(line, 1);
			ft_putline(line, g_env.cur_all_col, M_OTHER);
			while (j--)
				ft_move_right(line, 1);
		}
		else
			ft_putline(line, g_env.cur_all_col, M_OTHER);
	}
	if ((g_env.select_mode = !(g_env.select_mode)))
		g_env.select_pos =
		(((size_t)g_env.cur_all_col > (ft_strlen(line) - 1)) &&
		*line) ? g_env.cur_all_col - 1 : g_env.cur_all_col;
	else
		g_env.select_pos = 0;
}

void	ft_copy_line(char **line)
{
	if (g_env.select_mode)
	{
		if (g_env.select_line)
			ft_strdel(&(g_env.select_line));
		if (g_env.select_pos < g_env.cur_all_col)
			g_env.select_line = ft_strsub(*line, g_env.select_pos,
			g_env.cur_all_col - g_env.select_pos + 1);
		else
			g_env.select_line = ft_strsub(*line, g_env.cur_all_col,
			g_env.select_pos - g_env.cur_all_col + 1);
		ft_toggle_select(*line);
		g_env.select_char = 0;
	}
}

void	ft_cut_line(char **line)
{
	int i;

	if (g_env.select_mode)
	{
		if (g_env.select_line)
			ft_strdel(&(g_env.select_line));
		if (g_env.select_pos <= g_env.cur_all_col)
		{
			g_env.select_line = ft_strsub(*line,
			g_env.select_pos, g_env.cur_all_col - g_env.select_pos + 1);
			i = g_env.cur_all_col - g_env.select_pos + 1;
			while (i--)
				ft_backspace(line);
		}
		else
		{
			g_env.select_line = ft_strsub(*line, g_env.cur_all_col,
			g_env.select_pos - g_env.cur_all_col + 1);
			i = g_env.select_pos - g_env.cur_all_col + 1;
			while (i--)
				ft_delete(line);
		}
		ft_toggle_select(*line);
		g_env.select_char = 0;
	}
}

void	ft_paste_line(char **line)
{
	int i;

	if (g_env.select_line)
	{
		i = -1;
		while (g_env.select_line[++i])
			ft_putstr_char(g_env.select_line[i], line);
	}
}
