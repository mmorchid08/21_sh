/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:51:30 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/20 16:05:24 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

char		*ft_strjoin_one_charatcter(char const *s1, char const s2)
{
	int		i;
	char	*str;

	i = 0;
	if (s1 && s2)
	{
		str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1 + 1));
		if (!str)
			return (NULL);
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		str[i++] = s2;
		str[i] = '\0';
		return (str);
	}
	return (0);
}

void		ft_cut_buf(char *buf)
{
	buf[ft_strlen(buf) - 1] = '\0';
}

t_tokens	*new_node(char *data, int type)
{
	t_tokens	*node;

	node = (t_tokens *)malloc(sizeof(t_tokens));
	node->data = ft_strdup(data);
	node->type = type;
	node->status = 0;
	node->filename = NULL;
	node->here = NULL;
	node->args = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
