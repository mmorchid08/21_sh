/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:00:22 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 15:00:23 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_free_path(t_path **head)
{
	free((*head)->line);
	free((*head));
}

char	*ft_join_path(t_path *path)
{
	char *res;

	res = ft_strdup("/");
	while (path)
	{
		res = ft_free_strjoin(res, ft_strdup(path->line));
		if (path->next)
			res = ft_free_strjoin(res, ft_strdup("/"));
		path = path->next;
	}
	return (res);
}

t_path	*ft_new_path(char *path)
{
	t_path *tmp;

	if (!(tmp = (t_path *)malloc(sizeof(t_path))))
		exit(1);
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->line = path;
	return (tmp);
}

void	ft_pushback_path(t_path **head, t_path *new)
{
	t_path *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	ft_pushback_path(&(tmp->next), new);
}

void	ft_add_path(t_path **head, t_path *new)
{
	new->next = *head;
	*head = new;
}

void	ft_populate_path_list(t_path **head, char **split, int mode)
{
	int i;

	i = -1;
	while (split[++i])
	{
		if (mode)
			ft_pushback_path(head, ft_new_path(ft_strdup(split[i])));
		else
			ft_add_path(head, ft_new_path(ft_strdup(split[i])));
		free(split[i]);
	}
	free(split);
}

void	ft_remove_last_path(t_path **head)
{
	t_path *tmp;

	tmp = *head;
	if (tmp && !tmp->next)
	{
		ft_free_path(head);
		*head = NULL;
	}
	else
	{
		while (tmp && tmp->next && tmp->next->next)
			tmp = tmp->next;
		ft_free_path(&(tmp->next));
		tmp->next = NULL;
	}
}
