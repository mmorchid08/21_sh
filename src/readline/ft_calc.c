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
