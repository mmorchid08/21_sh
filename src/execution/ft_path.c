/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:00:22 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/20 14:54:54 by mmorchid         ###   ########.fr       */
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
