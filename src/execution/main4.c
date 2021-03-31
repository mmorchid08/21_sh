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

	if ((offset = ft_isaggr(c, "<&", 2)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, "<&", 2) == 0)
		return ((t_content){2, REDIRECTION_LEFT_AGGREGATION});
	if ((offset = ft_isaggr(c, "<", 1)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, "<", 1) == 0)
		return ((t_content){1, REDIRECTION_LEFT});
	if ((offset = ft_isaggr(c, ">", 1)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
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
	if ((*tmp)->type == PRE_AGGREGATION_NUMBER)
	{
		(*tmp)->next->pre_fd = ft_atoi((*tmp)->data);
		if ((*tmp)->prev)
		{
			arg = (*tmp)->next;
			(*tmp) = (*tmp)->prev;
			free_token(&((*tmp)->next));
			(*tmp)->next = arg;
		}
	}
}

void		append_list_tokens2(t_tokens **tmp, char *data, int type)
{
	if (((*tmp)->type == REDIRECTION_LEFT_AGGREGATION ||
(*tmp)->type == REDIRECTION_RIGHT_AGGREGATION) &&
ft_str_isdigit(data) && (*tmp)->sub_fd == -1)
		(*tmp)->sub_fd = ft_atoi(data);
	else if (((*tmp)->type == REDIRECTION_LEFT_AGGREGATION ||
(*tmp)->type == REDIRECTION_RIGHT_AGGREGATION) &&
ft_strequ(data, "-") && (*tmp)->close == 0)
		(*tmp)->close = 1;
	else if (check_red((*tmp)->type) && !((*tmp)->type == REDIRECTION_RIGHT_AGGREGATION && (*tmp)->pre_fd != -1 && (*tmp)->sub_fd != -1) && !(*tmp)->filename)
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
