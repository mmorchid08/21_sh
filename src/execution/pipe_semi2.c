/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_semi2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:28:34 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/20 16:16:36 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_exec_pipe(t_tokens *line, t_tokens *prev, int pipecount)
{
	ft_check_alias(&(line->data));
	ft_verify_non_fork_builtins(line);
	g_env.current_pid = fork();
	if (g_env.current_pid == 0)
	{
		if (g_env.fd_pipe && line->next && line->next->type == PIPE)
			dup2(g_env.fd_pipe[g_env.com_pipe * 2 + 1], STDOUT_FILENO);
		if (g_env.fd_pipe && prev && prev->next && prev->next->type == PIPE)
			dup2(g_env.fd_pipe[(g_env.com_pipe - 1) * 2], STDIN_FILENO);
		if (!line->next || (line->next->type != PIPE
		&& line->next->type != WORD))
			redirection(line);
		ft_unset_input_mode();
		ft_close_pipe(pipecount);
		if (ft_check_builtins(line->data) == 1)
		{
			ft_verify_builtins(line);
			exit(0);
		}
		else
			ft_exece(line);
	}
}

void	ft_exec_line_pipe_c1(int pipecount)
{
	ft_close_pipe(pipecount);
	ft_restore_fds();
	if (g_env.current_pid > 0)
	{
		g_env.running_proc = 1;
		while (pipecount--)
			wait(NULL);
		g_env.running_proc = 0;
	}
	ft_reset_input_mode();
}

void	ft_exec_line_pipe(t_tokens **node, int pipecount)
{
	t_tokens	*prev;
	int			pipefd_static[pipecount * 2];
	int			mult;

	mult = -2;
	g_env.fd_pipe = (int *)pipefd_static;
	while ((mult += 2) < pipecount * 2)
		if (pipe(g_env.fd_pipe + mult) < 0)
			exit(1);
	g_env.com_pipe = 0;
	ft_save_fds();
	prev = NULL;
	while ((*node))
	{
		ft_exec_pipe(*node, prev, pipecount * 2);
		if ((*node)->next && (*node)->next->type == PIPE)
		{
			prev = (*node);
			g_env.com_pipe++;
			(*node) = (*node)->next;
		}
		else
			break ;
		if ((*node))
			(*node) = (*node)->next;
	}
	ft_exec_line_pipe_c1(pipecount * 2);
}

void	handling_semi(t_tokens *node)
{
	while (node)
	{
		g_env.fd_pipe = NULL;
		if (node->next && node->next->type == PIPE)
			ft_exec_line_pipe(&node, ft_count_pipe(node->next));
		else if (node->type == 0)
			ft_exec(node);
		while (node && node->type == 0)
			node = node->next;
		if (!node)
			break ;
		node = node->next;
	}
}
