/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:16:40 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/23 17:02:01 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

t_var	*get_malloc_key_value(char *key, char *value)
{
	t_var	*nev;

	nev = (t_var *)malloc(sizeof(t_var));
	nev->key = key;
	nev->value = value;
	nev->next = NULL;
	return (nev);
}

void	ft_env_list(char **env)
{
	int			i;
	t_var	*tmp;
	char		**tab_env;

	tmp = NULL;
	i = 0;
	while (env[i])
	{
		tab_env = ft_strsplit(env[i], '=');
		if (tmp == NULL)
		{
			tmp = get_malloc_key_value(tab_env[0], tab_env[1]);
			g_env.var = tmp;
		}
		else
		{
			tmp->next = get_malloc_key_value(tab_env[0],
					tab_env[1]);
			tmp = tmp->next;
		}
		free(tab_env);
		i++;
	}
}
