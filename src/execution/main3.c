/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:18:01 by mmorchid          #+#    #+#             */
/*   Updated: 2021/04/15 13:47:07 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

t_content	check_character_for_split(char *c)
{
	int	offset;

	if (ft_strncmp(c, ">>", 2) == 0)
		return ((t_content){2, REDIRECTION_RIGHT_RIGHT});
	if (ft_strncmp(c, "<<<", 3) == 0)
		return ((t_content){3, REDIRECTION_LEFT_LEFT_LEFT});
	if (ft_strncmp(c, "<<", 2) == 0)
		return ((t_content){2, REDIRECTION_LEFT_LEFT});
	return (check_character_for_split2(c));
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
		tmp->data = ft_strmap2(tmp->data, &ft_decode_char);
		if (tmp->filename)
			tmp->filename = ft_strmap2(tmp->filename, &ft_decode_char);
		if (tmp->args)
			handling3(tmp->args);
		tmp = tmp->next;
	}
}
