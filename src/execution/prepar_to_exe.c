/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_semi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:33:00 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/12 18:54:33 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int		ft_count_tokens(t_tokens *token_begin)
{
	t_tokens	*tmp;
	int			count;

	count = 0;
	tmp = token_begin;
	while (tmp && tmp->type == 0)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int		ft_count_env()
{
	t_var	*tmp;
	int			count;

	count = 0;
	tmp = g_env.var;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**ft_convert_list_array(t_tokens *token_begin)
{
	char		**arr;
	t_tokens	*tmp;
	int			j;

	j = 0;
	tmp = token_begin;
	if (!(arr = (char **)malloc(sizeof(char *) * (ft_count_tokens(token_begin) + 1))))
		return (NULL);
	while (tmp && tmp->type == 0)
	{
		arr[j] = ft_strdup(tmp->data);
		j++;
		tmp = tmp->next;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_convert_var_array()
{
	char		**arr;
	t_var	*tmp;
	int			j;
	char		*join;
	char		*join2;

	j = 0;
	tmp = g_env.var;
	if (!(arr = (char **)malloc(sizeof(char *) * (ft_count_env() + 1))))
		return (NULL);
	while (tmp)
	{
		join = ft_strjoin(tmp->key, "=");
		join2 = ft_strjoin(join, tmp->value);
		arr[j] = ft_strdup(join2);
		free(join);
		free(join2);
		j++;
		tmp = tmp->next;
	}
	arr[j] = NULL;
	return (arr);
}