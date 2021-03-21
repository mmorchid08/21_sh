/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:18:01 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/20 16:51:35 by mmorchid         ###   ########.fr       */
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
