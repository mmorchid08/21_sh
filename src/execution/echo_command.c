/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:25:19 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/18 14:50:30 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int		ft_chek_espace(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

void	ft_operation_echo(t_tokens *token_begin)
{
	token_begin = token_begin->next;
	while (token_begin != NULL)
	{
		ft_putstr(token_begin->data);
		if (token_begin->next != NULL)
			write(1, " ", 1);
		token_begin = token_begin->next;
	}
	write(1, "\n", 1);
}
