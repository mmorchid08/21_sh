/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:49:07 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/20 14:51:01 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_env_function(void)
{
	t_var *tmp;

	tmp = g_env.var;
	while (tmp)
	{
		ft_putstr(tmp->key);
		ft_putchar('=');
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
}
