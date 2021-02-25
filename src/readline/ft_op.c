/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:00:03 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 15:00:06 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_putline_inner(char *str, int flag, int pos)
{
	int i;

	i = -1;
	if (g_env.select_char == 1 || g_env.select_char == 3)
		ft_putstr(C_SELECT);
	while (str[++i])
	{
		if (!flag && str[i] != '\n')
			ft_putchar(str[i]);
		else if (flag)
			ft_putchar(str[i]);
		if (g_env.select_mode && g_env.select_char == 4 && i == 0)
			ft_putstr(C_SELECT);
		if (g_env.select_char == 1 || g_env.select_char == 2 ||
	((g_env.select_char == 3 || (g_env.select_char == 4 && i >= 1))
	&& pos + i == g_env.select_pos))
		{
			ft_putstr(C_RESET);
			g_env.select_char = 0;
		}
		if (flag && (str[i + 1] == '\0' || str[i + 1] == '\n'))
			ft_putchar(' ');
	}
}

void	ft_putline(char *line, int pos, int mode)
{
	char	*tmp;
	int		len[3];

	ft_putstr(tgetstr("sc", NULL));
	tmp = (line + pos);
	len[2] = ft_strlen(line);
	len[0] = pos;
	while (len[0] >= 0 && (line)[len[0]] != '\n')
		len[0]--;
	len[1] = pos - 1;
	while (len[1] >= 0 && (line)[len[1]] && (line)[len[1]] != '\n')
		len[1]++;
	if (len[0] < 0)
		len[0] = len[1] + g_env.prompt_len - 1;
	else
		len[0] = ((pos - len[0]) + (len[1] - pos)) - 2;
	g_env.last_char_row = ((len[0] / g_env.col) + !!(len[0] % g_env.col));
	g_env.last_char_col = (len[0] % (g_env.col));
	len[0] = len[2] - 1;
	ft_putstr(tgetstr("cd", NULL));
	ft_putline_inner(tmp, len[0] != pos, pos);
	ft_putstr(tgetstr("rc", NULL));
	if (g_env.last_char_row + g_env.org_cur_y > g_env.row
	&& g_env.last_char_col == ((g_env.col - 1) * !!(mode)) && pos != len[0])
		ft_putstr(tgetstr("up", NULL));
}

void	ft_putstr_char(char c, char **line)
{
	char str[2];
	char *tmp;
	char *tmp2;

	str[1] = '\0';
	str[0] = c;
	if (!(*line))
		*line = ft_strdup(str);
	else
	{
		tmp = ft_free_strjoin(ft_strsub(*line,
		0, g_env.cur_all_col), ft_strdup(str));
		tmp2 = ft_free_strjoin(tmp, ft_strdup(*line + g_env.cur_all_col));
		free(*line);
		*line = tmp2;
	}
	ft_putline(*line, g_env.cur_all_col, M_INSERT);
	ft_move_right(*line, 1);
}

void	ft_backspace(char **line)
{
	char *tmp;

	if (*line && g_env.cur_all_col > 0)
	{
		ft_move_left(*line, 1);
		ft_putstr(tgetstr("cd", NULL));
		ft_putstr(tgetstr("sc", NULL));
		tmp = ft_free_strjoin(ft_strsub(*line, 0,
g_env.cur_all_col), ft_strdup((*line) + g_env.cur_all_col + 1));
		free(*line);
		*line = tmp;
		ft_putstr((*line + g_env.cur_all_col));
		ft_putstr(tgetstr("rc", NULL));
	}
}

void	ft_delete(char **line)
{
	char *tmp;

	if (*line && g_env.cur_all_col >= 0 &&
	(size_t)g_env.cur_all_col < ft_strlen(*line))
	{
		ft_putstr(tgetstr("cd", NULL));
		ft_putstr(tgetstr("sc", NULL));
		tmp = ft_free_strjoin(ft_strsub(*line, 0,
	g_env.cur_all_col), ft_strdup((*line) + g_env.cur_all_col + 1));
		free(*line);
		*line = tmp;
		ft_putstr((*line + g_env.cur_all_col));
		ft_putstr(tgetstr("rc", NULL));
	}
}
