/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_alias.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:55:24 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:55:26 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_save_alias(t_alias **al, char *alias, char *str)
{
	t_alias *tmp;

	tmp = *al;
	while (tmp)
	{
		if (ft_strequ(alias, tmp->alias))
		{
			free(tmp->alias);
			free(tmp->str);
			tmp->alias = alias;
			tmp->str = str;
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_alias(al, ft_new_alias(alias, str));
}

void	ft_list_alias(t_alias *al)
{
	while (al)
	{
		ft_putstr(al->alias);
		ft_putstr("=\'");
		ft_putstr(al->str);
		ft_putstr("\'\n");
		al = al->next;
	}
}

void	ft_operation_non_fork_alias(t_tokens *line)
{
	if (line && line->next && line->next->next)
	{
		ft_save_alias(&(g_env.al), ft_strdup(line->next), ft_strdup(line->next->next));
		ft_store_alias();
		line->status = 1;
	}
}
