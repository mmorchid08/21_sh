/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:39:41 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 18:41:37 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_store_his(void)
{
	int		fd;
	char	*tmp;
	t_his	*his;
	char	*path;

	path = F_H;
	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666)) >= 0)
	{
		his = g_env.his;
		while (his)
		{
			tmp = ft_strdup(his->line);
			ft_putendl_fd(ft_encode_line(tmp), fd);
			free(tmp);
			his = his->next;
		}
		close(fd);
	}
}

void	ft_load_his(void)
{
	int		fd;
	char	*tmp;
	char	*path;
	int		ret;

	path = F_H;
	if ((fd = open(path, O_RDONLY)) >= 0)
	{
		tmp = NULL;
		while ((ret = get_next_line(fd, &tmp)) > 0)
		{
			ft_push_his(&(g_env.his), ft_new_his(
			ft_strdup(ft_decode_line(tmp)), 0));
			ft_strdel(&tmp);
		}
		if (ret == -1)
			exit(1);
		ft_strdel(&tmp);
		if (g_env.gnl)
			ft_strdel(&(g_env.gnl));
		close(fd);
	}
}
