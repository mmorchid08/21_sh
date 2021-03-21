/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:18:01 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/21 13:02:29 by mmorchid         ###   ########.fr       */
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
	return (check_character_for_split2(c));
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

int			check_red(int type)
{
	if (type == 1 || type == 2 || type == 3 || type == 4
			|| type == 5 || type == 6 || type == 7)
		return (1);
	return (0);
}

void		handling2(char *line, t_vari *var,
		t_content *content, t_tokens **tokens)
{
	if (!(ft_isprint(line[var->i])
	|| (line[var->i] < 0 && line[var->i] >= -5)
	|| line[var->i] == '\n'))
		var->i++;
	while ((ft_isprint(line[var->i])
	|| (line[var->i] < 0 && line[var->i] >= -5)
	|| line[var->i] == '\n') && content->index == 0)
	{
		var->pt = var->token;
		var->token = ft_strjoin_one_charatcter(var->token, line[var->i]);
		ft_strdel(&var->pt);
		var->i++;
		*content = check_character_for_split(&line[var->i]);
		if (content->index != 0)
		{
			content->type = 0;
			break ;
		}
	}
	append_list_tokens(tokens, var->token, content->type);
	ft_bzero(var->token, ft_strlen(var->token));
	ft_strdel(&var->token);
}

void		handling3(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (check_red(tmp->type) && tmp->next != NULL && tmp->next->type == 0)
			tmp->next->type = REDIRECTION_WORD;
		if (tmp->type == 0)
			tmp->data = ft_strmap2(tmp->data, &ft_decode_char);
		tmp = tmp->next;
	}
}
