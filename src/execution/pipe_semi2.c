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

void	ft_exec_pipe(t_tokens **line, t_tokens *prev, int pipecount)
{
	t_tokens *tmp;

	tmp = *line;
	ft_check_alias(&(tmp->data));
	ft_verify_non_fork_builtins(tmp);
	g_env.current_pid = fork();
	if (g_env.current_pid == 0)
	{
		if (g_env.fd_pipe && tmp->next && tmp->next->type == PIPE)
			dup2(g_env.fd_pipe[g_env.com_pipe * 2 + 1], STDOUT_FILENO);
		if (g_env.fd_pipe && prev && prev->next && prev->next->type == PIPE)
			dup2(g_env.fd_pipe[(g_env.com_pipe - 1) * 2], STDIN_FILENO);
		if (!tmp->next || (tmp->next->type != PIPE
		&& tmp->next->type != WORD))
			redirection(&((*line)->next));
		ft_unset_input_mode();
		ft_close_pipe(pipecount);
		if (ft_check_builtins(tmp->data) == 1)
		{
			ft_verify_builtins(tmp);
			exit(0);
		}
		else
			ft_exece(tmp);
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
		(pipe(g_env.fd_pipe + mult) < 0) ? exit(1) : 1;
	g_env.com_pipe = 0;
	ft_save_fds();
	prev = NULL;
	while ((*node) && (*node)->type != SEMICOLON)
	{
		if ((*node)->type == WORD)
			ft_exec_pipe(node, prev, pipecount * 2);
		if ((*node)->next && (*node)->next->type == PIPE)
		{
			prev = (*node);
			g_env.com_pipe++;
			(*node) = (*node)->next;
		}
		((*node)) && ((*node) = (*node)->next);
	}
	ft_exec_line_pipe_c1(pipecount * 2);
}

int		ft_next_pipe(t_tokens *node)
{
	int flag;

	flag = 0;
	while (node)
	{
		if (node->type == SEMICOLON)
			break;
		if (node->type == PIPE)
			flag = 1;
		node = node->next;
	}
	return (flag);
}

void	handling_semi(t_tokens *node)
{
	while (node)
	{
		g_env.fd_pipe = NULL;
		if (node->next && ft_next_pipe(node->next))
			ft_exec_line_pipe(&node, ft_count_pipe(node->next));
		else if (node && node->type == 0)
			ft_exec(&node);
		if (!node)
			break ;
		node = node->next;
	}
}
