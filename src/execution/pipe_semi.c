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
	while (node && node->type == PIPE)
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


void	ft_exec(t_tokens *line)
{
	g_env.current_pid = fork();
	if (g_env.current_pid > 0)
	{
		g_env.running_proc = 1;
		waitpid(g_env.current_pid, 0, 0);
		// ft_reset_input_mode();
		g_env.running_proc = 0;
	}
	else if (g_env.current_pid == 0)
	{
		// ft_unset_input_mode();
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
		// ft_unset_input_mode();
		ft_close_pipe(pipecount);
		// if ((line->com).type >= 1 && (line->com).type <= 10)
		// 	ft_ext_builtin(line);
		// else if ((line->com).type == 0 && (!ft_exec_none_builtin(line)))
		// 	exit(0);
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
	// ft_reset_input_mode();
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
		ft_exec_pipe(*node, prev, pipecount * 2);
		if ((*node)->next->type == PIPE)
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
			// break ;
		g_env.fd_pipe = NULL;
		// if (node->type == PIPE)
		// 	ft_exec_line_pipe(&node, ft_count_pipe(node));
		// else 
        if (node->type == 0)
			ft_exec(node);
        while(node && node->type == 0)
            node = node->next;
		if (!node)
			break ;
		node = node->next;
	}
}

// void handling_semi(t_tokens *tokens, t_var *list_env)
// {
//     t_tokens *list;
//     t_tokens *start;
    
//     start = tokens;
//     list = tokens;
//     while (list)
//     {
//         if (list->type == SEMICOLON)
//         {   
//             handling_pipe(start,list,list_env);
//             start = list->next;
//         }
//         list = list->next;
//     }
//     if(start != NULL)
//         handling_pipe(start,list,list_env); 
// }


// void handling_pipe(t_tokens *start,t_tokens *list, t_var *list_env)
// {
//     t_tokens *begin;
//     t_fd fd;
//     pid_t pid;
//     int pos;
//     int count_pipe;
    
//     pos = 0;
//     count_pipe = 0;
//     begin = start;
//     ft_bzero(&fd,sizeof(fd));
//     while (start != list)
//     {
//         if (start->type == PIPE)
//         {
//             pipe(fd.fd_new);
//             count_pipe++;
//             pid = handling_command(begin,start,fd,pos,count_pipe,list_env);
//             fd.fd_old[1] = fd.fd_new[1];
//             fd.fd_old[0] = fd.fd_new[0];
//             pos = 1;
//             begin = start->next;
//         }    
//         start = start->next;
//     }
//     pos = 3;
//     pid = handling_command(begin,start, fd, pos, count_pipe,list_env);
//     waitpid(pid, 0, 0);
    
// }

// pid_t handling_command(t_tokens *begin,t_tokens *finish, t_fd fd, int pos, int count_pipe, t_var *list_env)
// {
//     pid_t pid;
//     t_tokens *tmp;
    
//     tmp  = begin;
//     if (count_pipe == 0 && ft_chek_builtins(begin->data) == 1)
//     {
//         int copy = dup(WRITE_END);
//         redirection(begin, finish);
//         ft_verify_builtins(begin, finish, list_env);
//         dup2(copy,1);
//         close(copy);
//         return(0);
//     }
//     pid = fork();
//     redirection(begin, finish);
//     if (pid == -1)
// 	{
// 		perror("fork failed");
// 		exit(EXIT_FAILURE);
// 	}
//     if (pid == 0)
//     {
//         if(pos == 0 || pos == 1)
//             dup2(fd.fd_new[WRITE_END], STDOUT_FILENO);
//         if(pos == 3 || pos == 1)
//             dup2(fd.fd_old[READ_END], STDIN_FILENO);
//         // ft_unset_input_mode();
//         // close(fd.fd_new[READ_END]);
//         // close(fd.fd_new[WRITE_END]);
//         close(fd.fd_old[WRITE_END]);
//         close(fd.fd_old[READ_END]);

//         if (ft_chek_builtins(tmp->data) == 1)
//         {
//             ft_verify_builtins(tmp,finish,list_env);
//             exit(0);
//         }
//         ft_exece(begin,finish, list_env);
//     }
//     else
//     {
//         // ft_reset_input_mode();
//         if(pos > 0 && count_pipe > 0)
//         {
//             close(fd.fd_old[READ_END]);
//             close(fd.fd_old[WRITE_END]);
//         }
//     }
//     return(pid);
// }