/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_semi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:33:00 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/31 17:18:53 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_save_fds(void)
{
	g_env.res_stdin = dup(STDIN_FILENO);
	g_env.res_stdout = dup(STDOUT_FILENO);
	g_env.res_stderr = dup(STDERR_FILENO);
}

void	ft_restore_fds(void)
{
	dup2(g_env.res_stdin, STDIN_FILENO);
	dup2(g_env.res_stdout, STDOUT_FILENO);
	dup2(g_env.res_stderr, STDERR_FILENO);
}

int		ft_count_pipe(t_tokens *node)
{
	int i;

	i = 0;
	while (node && node->type != SEMICOLON)
	{
		if (node->type == PIPE)
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

void	ft_exec(t_tokens **line)
{
	t_tokens *tmp;

	tmp = *line;
	ft_check_alias(&(tmp->data));
	ft_verify_non_fork_builtins(tmp);
	g_env.current_pid = fork();
	if (g_env.current_pid > 0 && (g_env.running_proc = 1))
	{
		waitpid(g_env.current_pid, 0, 0);
		ft_reset_input_mode();
		g_env.running_proc = 0;
	}
	else if (g_env.current_pid == 0)
	{
		if (!redirection(&((*line)->next)))
			exit(1);
		ft_unset_input_mode();
		if (ft_check_builtins(tmp->data) == 1)
		{
			ft_verify_builtins(tmp);
			exit(0);
		}
		else
			ft_exece(tmp);
	}
}
