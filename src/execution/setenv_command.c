/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:59:30 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/24 17:53:34 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_delete_one_env(t_list_env **env_list,
		t_tokens *token_begin, t_tokens *token_finish)
{
	t_list_env	**tmp;
	t_list_env	*to_free;

	token_begin = token_begin->next;
	while (token_begin != token_finish)
	{
		tmp = env_list;
		while (*tmp)
		{
			if (ft_strequ((*tmp)->key, token_begin->data))
			{
				to_free = *tmp;
				*tmp = to_free->next;
				free(to_free->key);
				free(to_free->value);
				free(to_free);
				break ;
			}
			tmp = &(*tmp)->next;
		}
		token_begin = token_begin->next;
	}
}

void	ft_add_to_env(t_data_env data_env, t_list_env **list_env)
{
	t_list_env	*go_to_end;
	t_list_env	*tmp;
	t_list_env	*new_node;
	int			i;

	go_to_end = *list_env;
	tmp = *list_env;
	i = 0;
	while (go_to_end)
	{
		if (ft_strcmp(go_to_end->key, data_env.key) == 0 && ++i)
			go_to_end->value = ft_strdup(data_env.value);
		go_to_end = go_to_end->next;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (i == 0)
	{
		new_node = get_malloc_key_value(data_env.key, data_env.value);
		tmp->next = new_node;
	}
}

void	ft_cat_new_env_to_key_value(t_data_env *data_env, char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '=')
		i++;
	data_env->key = ft_strsub(buf, 0, i);
	data_env->value = ft_strdup(buf + 1 + i);	
}

void	ft_add_change_env(t_tokens *token_begin, t_list_env *list_env)
{
	t_data_env	data_env;

	token_begin = token_begin->next;
	while (token_begin)
	{
		if (ft_strchr(token_begin->data, '=') == NULL)
			break ;
		ft_cat_new_env_to_key_value(&data_env, token_begin->data);
		ft_add_to_env(data_env, &list_env);
		token_begin = token_begin->next;
	}
}
