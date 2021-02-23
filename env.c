/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:49:07 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/23 17:08:03 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	free_list_env(t_list_env **env)
{
	t_list_env	*current;
	t_list_env	*next;

	current = *env;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

void	ft_env_function(t_list_env *env)
{
	char	*name;

	while (env)
	{
		ft_putstr(env->key);
		ft_putchar('=');
		ft_putendl(env->value);
		env = env->next;
	}
}
