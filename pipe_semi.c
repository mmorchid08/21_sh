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

void handling_semi(t_tokens *tokens, t_list_env *list_env)
{
    t_tokens *list;
    t_tokens *start;
    
    start = tokens;
    list = tokens;
    while (list)
    {
        if (list->type == SEMICOLON)
        {    
            handling_pipe(start,list,list_env);
                start = list->next;
        }
        list = list->next;
    }
    if(start != NULL)
        handling_pipe(start,list,list_env); 
}

void handling_pipe(t_tokens *start,t_tokens *list, t_list_env *list_env)
{
    t_tokens *begin;
    t_fd fd;
    pid_t pid;
    int pos;
    int count_pipe;
    
    pos = 0;
    count_pipe = 0;
    begin = start;
    ft_bzero(&fd,sizeof(fd));
    while (start != list)
    {
        if (start->type == PIPE)
        {
            pipe(fd.fd_new);
            count_pipe++;
            pid = handling_command(begin,start,fd,pos,count_pipe,list_env);
            fd.fd_old[1] = fd.fd_new[1];
            fd.fd_old[0] = fd.fd_new[0];
            pos = 1;
            begin = start->next;
        }    
        start = start->next;
    }
    pos = 3;
    pid = handling_command(begin,start, fd, pos, count_pipe,list_env);
    waitpid(pid, 0, 0);
    
}

pid_t handling_command(t_tokens *begin,t_tokens *finish, t_fd fd, int pos, int count_pipe, t_list_env *list_env)
{
    pid_t pid;
    t_tokens *tmp;
    
    tmp  = begin;
    if (count_pipe == 0 && ft_chek_builtins(begin->data) == 1)
    {
        int copy = dup(WRITE_END);
        redirection(begin, finish);
        ft_verify_builtins(begin, finish, list_env);
        dup2(copy,1);
        close(copy);
        return(0);
    }
    pid = fork();
    if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
    if (pid == 0)
    {
        if(pos == 0 || pos == 1)
        {
            dup2(fd.fd_new[WRITE_END], STDOUT_FILENO);
            close(fd.fd_new[READ_END]);
            close(fd.fd_new[WRITE_END]);
        }
        if(pos == 3 || pos == 1)
        {
            dup2(fd.fd_old[READ_END], STDIN_FILENO);
            close(fd.fd_old[WRITE_END]);
            close(fd.fd_old[READ_END]);
        }
        redirection(begin, finish);
        if (ft_chek_builtins(tmp->data) == 1)
        {  
            ft_verify_builtins(tmp,finish,list_env);
            exit(0);
        }
        ft_exece(begin,finish, list_env);
        exit(0);
    }
    else
    {
        if(pos > 0 && count_pipe > 0)
        {
            close(fd.fd_old[READ_END]);
            close(fd.fd_old[WRITE_END]);
        }
    }
    return(pid);
}