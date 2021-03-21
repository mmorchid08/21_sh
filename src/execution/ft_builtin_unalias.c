/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unalias.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:56:31 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:56:35 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int		ft_remove_unalias(t_alias **al, char *alias)
{
	t_alias	*tmp;
	t_alias	*prev;

	tmp = *al;
	if (tmp && ft_strequ(tmp->alias, alias))
	{
		free(tmp);
		*al = tmp->next;
		ft_store_alias();
		return (1);
	}
	while (tmp)
	{
		if (ft_strequ(tmp->alias, alias))
		{
			prev->next = tmp->next;
			free(tmp);
			ft_store_alias();
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	ft_operation_non_fork_unalias(t_tokens *line)
{
	if (line && line->next)
	{
		line->status = 1;
		line = line->next;
		while (line)
		{
			if (!(line->ret = ft_remove_unalias(&(g_env.al), line)))
			{
				line->status = 0;
				break ;
			}
			line = line->next;
		}
	}
}
