/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:18:01 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/28 13:29:41 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

t_content	check_character_for_split2(char *c)
{
	int	offset;

	if (ft_strncmp(c, "<", 1) == 0)
		return ((t_content){1, REDIRECTION_LEFT});
	if (ft_strncmp(c, ">", 1) == 0)
		return ((t_content){1, REDIRECTION_RIGHT});
	if (ft_strncmp(c, "|", 1) == 0)
		return ((t_content){1, PIPE});
	if (ft_strncmp(c, ";", 1) == 0)
		return ((t_content){1, SEMICOLON});
	if ((ft_strncmp(c, " ", 1) == 0) || (ft_strncmp(c, "\t", 1) == 0))
		return ((t_content){1, SPACE});
	return ((t_content){0, 0});
}

void		append_list_tokens3(t_tokens **tmp, char *data, int type)
{
	t_tokens	*arg;

	(*tmp)->next = new_node(data, type);
	(*tmp)->next->prev = (*tmp);
}

void		append_list_tokens2(t_tokens **tmp, char *data, int type)
{
	if (check_red((*tmp)->type) && !(*tmp)->filename)
		(*tmp)->filename = ft_strdup(data);
	else
	{
		if (type == WORD && (*tmp)->type == WORD)
			append_list_tokens(&((*tmp)->args), data, WORD_ARG);
		else
		{
			(*tmp)->next = new_node(data, type);
			(*tmp)->next->prev = (*tmp);
			if (type == WORD)
				(*tmp)->next->args = new_node((*tmp)->next->data, WORD_ARG);
		}
	}
}

void		append_list_tokens(t_tokens **tokens, char *data, int type)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (tmp == NULL)
	{
		tmp = new_node(data, type);
		if (type == WORD)
			tmp->args = new_node(tmp->data, WORD_ARG);
		*tokens = tmp;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (check_red(type))
			append_list_tokens3(&tmp, data, type);
		else
			append_list_tokens2(&tmp, data, type);
	}
}

int			check_red(int type)
{
	if (type == 1 || type == 2 || type == 3 || type == 4
			|| type == 5 || type == 6 || type == 7)
		return (1);
	return (0);
}
