/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:54:33 by youarzaz          #+#    #+#             */
/*   Updated: 2021/04/11 17:34:50 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

t_alias		*ft_new_alias(char *alias, char *str)
{
	t_alias *al;

	if (!(al = (t_alias *)malloc(sizeof(t_alias))))
		exit(1);
	al->next = NULL;
	al->alias = alias;
	al->str = str;
	return (al);
}

void		ft_add_alias(t_alias **head, t_alias *new)
{
	// printf("******************\n");
	// printf("new alias =%s str for alias = %s\n", new->alias, new->str);
	if (!*head)
		*head = new;
	else
	{
		new->next = *head;
		*head = new;
	}
}

void		ft_store_alias(void)
{
	int		fd;
	char	*tmp;
	t_alias	*alias;
	char	*path;

	path = F_AL;
	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666)) >= 0)
	{
		alias = g_env.al;
		while (alias)
		{
			tmp = ft_strdup(alias->alias);
			ft_putstr_fd(ft_encode_line(tmp), fd);
			free(tmp);
			ft_putchar_fd(';', fd);
			tmp = ft_strdup(alias->str);
			ft_putendl_fd(ft_encode_line(tmp), fd);
			free(tmp);
			alias = alias->next;
		}
		close(fd);
	}
}

void		ft_load_alias(void)
{
	int		fd;
	int		ret;
	char	*line;
	char	**al;
	char	*path;

	path = F_AL;
	if ((fd = open(path, O_RDONLY)) >= 0)
	{
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			(!(al = ft_strsplit(line, ';'))) ? exit(1) : 1;
			ft_add_alias(&(g_env.al), ft_new_alias(ft_strdup(
			ft_decode_line(al[0])), ft_strdup(ft_decode_line(al[1]))));
			ft_free_table(&al);
			ft_strdel(&line);
		}
		(ret == -1) ? exit(1) : 1;
		ft_strdel(&line);
		if (g_env.gnl)
			ft_strdel(&(g_env.gnl));
		close(fd);
	}
}

void		ft_check_alias(char **line)
{
	t_alias *al;

	al = g_env.al;
	while (al)
	{
		if (ft_strequ(*line, al->alias))
		{
			free(*line);
			*line = ft_strdup(al->str);
		}
		al = al->next;
	}
}
