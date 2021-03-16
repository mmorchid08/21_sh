/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_semi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:33:00 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/24 18:09:59 by mmorchid         ###   ########.fr       */
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
	while (node && (node->type == PIPE || node->type == WORD))
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


void	ft_exec(t_tokens *line)
{
	g_env.current_pid = fork();
	if (g_env.current_pid > 0)
	{
		g_env.running_proc = 1;
		waitpid(g_env.current_pid, 0, 0);
		ft_reset_input_mode();
		g_env.running_proc = 0;
	}
	else if (g_env.current_pid == 0)
	{
        if (ft_chek_builtins(line->data) == 1)
        {
            ft_verify_builtins(line);
            exit(0);
        }
        else
            ft_exece(line);
	}
}

void	ft_exec_pipe(t_tokens *line, t_tokens *prev, int pipecount)
{
	g_env.current_pid = fork();
	if (g_env.current_pid == 0)
	{
		if (g_env.fd_pipe && line->next && line->next->type == PIPE)
			dup2(g_env.fd_pipe[g_env.com_pipe * 2 + 1], STDOUT_FILENO);
		if (g_env.fd_pipe && prev && prev->next && prev->next->type == PIPE)
			dup2(g_env.fd_pipe[(g_env.com_pipe - 1) * 2], STDIN_FILENO);
		ft_unset_input_mode();
		ft_close_pipe(pipecount);
        if (ft_chek_builtins(line->data) == 1)
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
    t_tokens *prev;
	int pipefd_static[pipecount * 2];
	int mult;


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
		printf("[%d]\n", (*node)->type);
		// ft_exec_pipe(*node, prev, pipecount * 2);
		// if ((*node)->next && (*node)->next->type == PIPE)
		// {
        //     prev = (*node);
        //     g_env.com_pipe++;
        //     (*node) = (*node)->next;
        // }
		// else
		// 	break ;
        // if ((*node))
		    (*node) = (*node)->next;
	}
	// ft_exec_line_pipe_c1(pipecount * 2);
}

void	handling_semi(t_tokens *node)
{
	while (node)
	{
		// while (node && node->prev && node->prev->op_main
		// & O_AND && !node->prev->status)
		// {
		// 	node->status = 0;
		// 	node = node->next;
		// }
		// if (node && node->prev && node->prev->op_main
		// & O_OR && node->prev->status)
		// 	while (node && node->prev && node->prev->op_main & O_OR)
		// 		node = node->next;
		// if (!node)
		// 	break ;
		g_env.fd_pipe = NULL;
		if (node->next && node->next->type == PIPE)
			ft_exec_line_pipe(&node, ft_count_pipe(node->next));
		else 
        if (node->type == 0)
			ft_exec(node);
        while(node && node->type == 0)
            node = node->next;
		if (!node)
			break ;
		node = node->next;
	}
}
