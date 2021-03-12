/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:49:07 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/24 17:53:00 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	free_list_env()
{
	t_var	*current;
	t_var	*next;

	current = g_env.var;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	g_env.var = NULL;
}

void	ft_env_function()
{
	t_var *env;
	
	env = g_env.var;
	while (env)
	{
		ft_putstr(env->key);
		ft_putchar('=');
		ft_putendl(env->value);
		env = env->next;
	}
}
