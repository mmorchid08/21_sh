/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:57:12 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:57:35 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		ft_echo_char(int c)
{
	ft_putchar(c);
	return (1);
}

char	*ft_encode_line(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			str[i] = -1;
		else if (str[i] == '$')
			str[i] = -2;
		else if (str[i] == '|')
			str[i] = -3;
		else if (str[i] == ';')
			str[i] = -4;
		else if (str[i] == '\n')
			str[i] = -7;
		else if (str[i] == '&')
			str[i] = -8;
	return (str);
}

char	*ft_decode_line(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == -1)
			str[i] = ' ';
		else if (str[i] == -2)
			str[i] = '$';
		else if (str[i] == -3)
			str[i] = '|';
		else if (str[i] == -4)
			str[i] = ';';
		else if (str[i] == -7)
			str[i] = '\n';
		else if (str[i] == -8)
			str[i] = '&';
	return (str);
}

int		ft_count_pipe(t_line *node)
{
	int i;

	i = 0;
	while (node && node->op_main & O_PIPE)
	{
		i++;
		node = node->next;
	}
	return ((i == 0) ? 1 : i);
}

void	ft_close_pipe(int pipecount)
{
	while (pipecount-- > 0)
		close(g_env.fd_pipe[pipecount]);
}
