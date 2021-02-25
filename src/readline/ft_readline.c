/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:00:40 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 15:00:41 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		ft_isnonprint(char c)
{
	if (c == '\n' || c == '\t')
	{
		return (1);
	}
	return (0);
}

void	ft_readline_c3(void)
{
	if (g_env.num == K_LEFT && !(g_env.cur_mult_col = 0))
		ft_move_left(g_env.line, 0);
	else if (g_env.num == K_RIGHT && !(g_env.cur_mult_col = 0))
		ft_move_right(g_env.line, 0);
	else if (g_env.num == K_HOME)
		ft_move_home(g_env.line, 0);
	else if (g_env.num == K_END)
		ft_move_end(g_env.line, 0);
	else if (g_env.num == K_BACKSPACE)
		ft_backspace(&(g_env.line));
	else if (g_env.num == K_DEL)
		ft_delete(&(g_env.line));
	else if (g_env.num == K_UP)
		ft_move_up(&(g_env.line));
	else if (g_env.num == K_DOWN)
		ft_move_down(&(g_env.line));
	else if (g_env.num == K_ALTS)
		ft_toggle_select(g_env.line);
	else if (g_env.num == K_ALTC)
		ft_copy_line(&(g_env.line));
	else if (g_env.num == K_ALTX)
		ft_cut_line(&(g_env.line));
	else if (g_env.num == K_ALTV)
		ft_paste_line(&(g_env.line));
}

void	ft_readline_c2(char *buff)
{
	ft_readline_c3();
	if (g_env.num == K_ALTUP)
		ft_line_up(&(g_env.line));
	else if (g_env.num == K_ALTDOWN)
		ft_line_down(&(g_env.line));
	else if (g_env.num == K_ALTLEFT)
		ft_word_left(g_env.line);
	else if (g_env.num == K_ALTRIGHT)
		ft_word_right(g_env.line);
	else if (g_env.num == K_TAB)
		ft_autocompletion(&(g_env.line));
	else if (g_env.num == K_CTRLD)
		ft_controle_d(&(g_env.line));
	else
	{
		g_env.num = -1;
		while (buff[++g_env.num] && (ft_isprint(buff[g_env.num])
		|| ft_isnonprint(buff[g_env.num])))
			ft_putstr_char(buff[g_env.num], &(g_env.line));
	}
}

void	ft_readline_c1(void)
{
	ft_get_cursor_coor(&(g_env.org_cur_x), &(g_env.org_cur_y));
	g_env.cur_col = 0;
	g_env.cur_row = 0;
	g_env.cur_all_col = 0;
	g_env.cur_all_row = 0;
	g_env.cur_mult_col = 0;
	g_env.select_mode = 0;
	g_env.select_pos = 0;
	g_env.num = -1;
	g_env.line = ft_strnew(0);
	(g_env.num == -1) ? dup2(g_env.res_stdin, 0) : 1;
	g_env.num = 0;
}

char	*ft_readline(void)
{
	char buff[MAX_BUFF];

	ft_readline_c1();
	ft_bzero(buff, MAX_BUFF);
	while (1)
		if (read(0, buff, MAX_BUFF) > 0)
		{
			g_env.num = (int)(*((int *)buff));
			if (g_env.num == K_ENTER)
			{
				ft_enter();
				break ;
			}
			else
				ft_readline_c2((char *)buff);
			g_env.num = 0;
			ft_bzero(buff, MAX_BUFF);
		}
		else
			break ;
	return (g_env.line);
}
