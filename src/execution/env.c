/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:49:07 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/18 14:50:05 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

// void	free_list_env(t_list_env **env)
// {
// 	t_list_env	*current;
// 	t_list_env	*next;

// 	current = *env;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->key);
// 		free(current->value);
// 		free(current);
// 		current = next;
// 	}
// 	*env = NULL;
// }

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
