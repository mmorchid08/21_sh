/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:59:43 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:59:44 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_move_right_c1(char *line)
{
	if ((g_env.cur_col > 0 && ((g_env.cur_row == 0 && g_env.cur_col +
g_env.prompt_len == (size_t)g_env.col - 1) || (g_env.cur_row > 0 &&
g_env.cur_col == g_env.col - 1))) || line[g_env.cur_all_col] == '\n')
	{
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		g_env.cur_col = 0;
		g_env.cur_all_col++;
		g_env.cur_row++;
		g_env.cur_all_row++;
	}
	else
	{
		ft_putstr(tgetstr("nd", NULL));
		g_env.cur_col++;
		g_env.cur_all_col++;
	}
}

void	ft_move_right(char *line, int mode)
{
	if (line && g_env.cur_all_col < (int)ft_strlen(line))
	{
		if ((!mode || mode == 2) && g_env.select_mode)
		{
			if (g_env.cur_all_col >= g_env.select_pos)
				g_env.select_char = 1;
			else
				g_env.select_char = 4;
			ft_putline(line, g_env.cur_all_col, M_OTHER);
		}
		ft_move_right_c1(line);
	}
}

void	ft_move_left_c1(char *line)
{
	int i;

	i = 1;
	while (g_env.cur_all_col - 1 - i >= 0 &&
	line[g_env.cur_all_col - 1 - i] != '\n')
		i++;
	if (g_env.cur_all_col - 1 - i < 0 &&
	(i + (int)g_env.prompt_len) >= g_env.col)
		i = (i + g_env.prompt_len) % g_env.col;
	else if (g_env.cur_all_col - 1 - i >= 0 && i >= g_env.col)
		i = (i % g_env.col == 0) ? g_env.col : i % g_env.col;
	ft_putstr(tgetstr("up", NULL));
	if (g_env.cur_row == 1)
		ft_putstr(tgoto(tgetstr("ch", NULL),
		g_env.prompt_len + i - 1, g_env.prompt_len + i - 1));
	else
		ft_putstr(tgoto(tgetstr("ch", NULL), i - 1, i - 1));
	g_env.cur_col = i - 1;
	g_env.cur_all_col--;
	g_env.cur_row--;
	g_env.cur_all_row--;
}

void	ft_move_left_c2(char *line, int mode)
{
	if ((!mode || mode == 2) && g_env.select_mode)
	{
		if (g_env.cur_all_col <= g_env.select_pos)
			g_env.select_char = 3;
		else
			g_env.select_char = 2;
		ft_putline(line, g_env.cur_all_col, M_OTHER);
	}
}

void	ft_move_left(char *line, int mode)
{
	if (g_env.cur_all_col > 0)
	{
		if (g_env.cur_col == 0 && line[g_env.cur_all_col - 1] == '\n')
			ft_move_left_c1(line);
		else if (g_env.cur_col == 0)
		{
			ft_putstr(tgetstr("up", NULL));
			ft_putstr(tgoto(tgetstr("ch", NULL),
			g_env.col - 1, g_env.col - 1));
			g_env.cur_col = (g_env.cur_row == 1) ?
			(g_env.col - 1) - g_env.prompt_len : (size_t)g_env.col - 1;
			g_env.cur_all_col--;
			g_env.cur_row--;
			g_env.cur_all_row--;
		}
		else
		{
			ft_putstr(tgetstr("le", NULL));
			g_env.cur_col--;
			g_env.cur_all_col--;
		}
		ft_move_left_c2(line, mode);
	}
}
