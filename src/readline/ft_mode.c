/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:59:32 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:59:35 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_set_input_mode(void)
{
	struct termios tattr;

	if (!isatty(0))
		exit(EXIT_FAILURE);
	tcgetattr(STDIN_FILENO, &(g_env.org_tattr));
	tattr = g_env.org_tattr;
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(tattr));
}

void	ft_reset_input_mode(void)
{
	struct termios tattr;

	tattr = g_env.org_tattr;
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(tattr));
}

void	ft_unset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(g_env.org_tattr));
}
