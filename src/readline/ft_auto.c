/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:55:08 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:55:09 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_auto_check(t_di *filtred, int len, char **line)
{
	t_di	*tmp;
	t_di	*store;
	char	c;
	int		i;

	tmp = filtred;
	i = len;
	while (filtred)
	{
		if ((store = tmp) && !store->name[len])
			break ;
		c = store->name[len];
		while (store)
		{
			if (store->next && store->name[len] != store->next->name[len])
				break ;
			store = store->next;
		}
		if (store)
			break ;
		ft_putstr_char(c, line);
		len++;
	}
	(i == len) ? ft_putchar('\a') : 1;
	ft_free_dir(&tmp);
}

void	ft_auto_process_paths(t_di **filtred, char *name, char **paths, int len)
{
	t_di	*tmp;
	t_di	*store;
	int		i;

	i = -1;
	while (paths[++i])
	{
		store = ft_load_dir(paths[i]);
		while (store)
		{
			if (ft_strnequ(store->name, name, len))
				ft_add_dir(filtred, ft_new_dir(ft_strdup(store->name)));
			tmp = store->next;
			free(store->name);
			free(store);
			store = tmp;
		}
	}
}

void	ft_auto_process(char **line)
{
	char	**paths;
	char	*name;
	t_di	*filtred;
	int		len;

	filtred = NULL;
	if ((name = ft_get_var_value(g_env.var, "PATH")))
	{
		paths = ft_strsplit(name, ':');
		name = ft_strsub(*line, 0, g_env.cur_all_col);
		len = ft_strlen(name);
		ft_auto_process_paths(&filtred, name, paths, len);
		ft_free_table(&paths);
		free(name);
		ft_auto_check(filtred, len, line);
	}
}

void	ft_autocompletion(char **line)
{
	int i;

	if (*line)
	{
		i = g_env.cur_all_col;
		while (i > 0)
			if ((*line)[--i] == ' ')
			{
				ft_putchar('\a');
				return ;
			}
		ft_auto_process(line);
	}
}
