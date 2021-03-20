/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:18:01 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/20 16:51:35 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

t_content	check_character_for_split(char *c)
{
	int	offset;

	if ((offset = ft_isaggr(c, ">>", 2)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, ">>", 2) == 0)
		return ((t_content){2, REDIRECTION_RIGHT_RIGHT});
	if ((offset = ft_isaggr(c, "<<<", 3)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, "<<<", 3) == 0)
		return ((t_content){3, REDIRECTION_LEFT_LEFT_LEFT});
	if ((offset = ft_isaggr(c, "<<", 2)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, "<<", 2) == 0)
		return ((t_content){2, REDIRECTION_LEFT_LEFT});
	if ((offset = ft_isaggr(c, ">&", 2)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, ">&", 2) == 0)
		return ((t_content){2, REDIRECTION_RIGHT_AGGREGATION});
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

void	append_list_tokens(t_tokens **tokens, char *data, int type)
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
		if (type == WORD && tmp->type == WORD)
			append_list_tokens(&(tmp->args), data, WORD_ARG);
		else
		{
			tmp->next = new_node(data, type);
			if (type == WORD)
				tmp->next->args = new_node(tmp->next->data, WORD_ARG);
		}
	}
}

int		check_red(int type)
{
	if (type == 1 || type == 2 || type == 3 || type == 4
			|| type == 5 || type == 6 || type == 7)
		return (1);
	return (0);
}
