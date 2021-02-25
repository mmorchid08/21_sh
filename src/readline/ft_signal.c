/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:01:01 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 15:01:02 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_signal_handler(int num)
{
	if (num == 2)
	{
		if (g_env.running_proc)
		{
			kill(g_env.current_pid, 0);
			g_env.current_pid = 0;
			ft_reset_input_mode();
		}
		else
			ft_putstr_fd("^C", 2);
		g_env.inside_prompt = -1;
		g_env.num = -1;
		close(0);
		ft_putstr("\n");
	}
	else if (num == 28)
		ft_size_init();
}

void	ft_signal_handle(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGTSTP, ft_signal_handler);
	signal(SIGWINCH, ft_signal_handler);
}
