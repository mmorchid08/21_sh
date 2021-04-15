/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 00:24:38 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/10 00:26:59 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_tononprint(char **str)
{
	int		i;
	char	c[3];
	char	*tmp;

	i = -1;
	c[0] = '\\';
	c[2] = '\0';
	while (*str && (*str)[++i])
	{
		c[1] = -1;
		((*str)[i] == '\a') && (c[1] = 'a');
		((*str)[i] == '\b') && (c[1] = 'b');
		((*str)[i] == '\e') && (c[1] = 'e');
		((*str)[i] == '\f') && (c[1] = 'f');
		((*str)[i] == '\n') && (c[1] = 'n');
		((*str)[i] == '\r') && (c[1] = 'r');
		((*str)[i] == '\t') && (c[1] = 't');
		((*str)[i] == '\v') && (c[1] = 'v');
		((c[1] != -1)) && ((*str)[i] = '\0');
		((c[1] != -1)) && (tmp = ft_strdup((*str) + i + 1));
		((c[1] != -1)) && ((*str) = ft_free_strjoin((*str), ft_strdup(c)));
		((c[1] != -1)) && ((*str) = ft_free_strjoin((*str), tmp));
	}
}

void	ft_controle_d(char **line)
{
	if (g_env.inside_heredoc == 1)
	{
		g_env.inside_heredoc = -1;
		ft_putendl_fd("^D", 2);
	}
	else if ((!*line || !**(line)))
	{
		ft_putendl_fd("^D", 2);
		ft_exec_exit();
	}
	else
		ft_delete(line);
}

void	ft_enter(void)
{
	t_his *tmp;

	if (g_env.line && *(g_env.line))
		ft_move_end(g_env.line, 1);
	ft_putchar('\n');
	while (g_env.his && g_env.his->next)
		g_env.his = g_env.his->next;
	while (g_env.his && g_env.his->prev)
	{
		free(g_env.his->dis_line);
		g_env.his->dis_line = ft_strdup(g_env.his->line);
		g_env.his = g_env.his->prev;
	}
	if (g_env.his && g_env.his->next && g_env.his->type)
	{
		free(g_env.his->line);
		free(g_env.his->dis_line);
		tmp = g_env.his->next;
		free(g_env.his);
		g_env.his = tmp;
		g_env.his->prev = NULL;
	}
}
