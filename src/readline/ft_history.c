/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:58:48 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:58:52 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_his	*ft_new_his(char *line, int type)
{
	t_his *his;

	if (!(his = (t_his *)malloc(sizeof(t_his))))
		exit(1);
	his->next = NULL;
	his->prev = NULL;
	his->line = line;
	his->dis_line = ft_strdup(line);
	his->type = type;
	if (his->type)
		his->cur = -1;
	return (his);
}

void	ft_add_his(t_his **head, t_his *new)
{
	if (!*head)
		*head = new;
	else
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
	}
}

void	ft_push_his(t_his **head, t_his *new)
{
	if (!*head)
	{
		*head = new;
		return ;
	}
	else if (!(*head)->next)
	{
		(*head)->next = new;
		new->prev = *head;
		return ;
	}
	ft_push_his(&((*head)->next), new);
}

void	ft_save_his(char *line, int type)
{
	if (!ft_strequ(line, "exit"))
	{
		ft_add_his(&(g_env.his), ft_new_his(line, type));
		if (!type)
			ft_store_his();
	}
	else
		ft_strdel(&line);
}
