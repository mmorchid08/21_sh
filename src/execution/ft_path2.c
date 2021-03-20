/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:53:31 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/20 14:54:22 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

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
