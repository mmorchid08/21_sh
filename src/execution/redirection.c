/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:52:46 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/03 18:09:24 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void redirection_out(char *file_name)   /*  >   */
{
    int out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    dup2(out,WRITE_END);
    close(out);
}

void redirection_out_out(char *file_name)   /*  >>  */
{
    int out_out = open(file_name, O_APPEND |O_WRONLY | O_CREAT, 0600);
    dup2(out_out,WRITE_END);
    close(out_out);
}

void redirection_in(char *file_name) /*    <   */
{
    int in = open(file_name, O_RDONLY);
    dup2(in,READ_END);
    close(in);
}

void ft_heredoc(char *line)
{
    char *str;
    char *tmp;

    g_env.prompt_len = ft_strlen("heredoc> ");
    str = NULL;
    while(1)
    {
        ft_putstr("heredoc> ");
        tmp = ft_readline();
        if (ft_strequ(tmp, line))
            break;
        if (tmp)
        {
            str = (str)? ft_free_strjoin(str, ft_strdup("\n")) : ft_strnew(0);
            str = ft_free_strjoin(str, tmp);
        }
        
    }
    g_env.current_pid = fork();
    if (g_env.current_pid > 0)
    {
        waitpid(g_env.current_pid, 0, 0);
        exit(0);
    }
    else if (g_env.current_pid == 0)
    {
        ft_putendl_fd(str, 0);
        exit(0);
    }
}

void ft_herestr(char *line)
{
    g_env.current_pid = fork();
    if (g_env.current_pid > 0)
    {
        waitpid(g_env.current_pid, 0, 0);
        exit(0);
    }
    else if (g_env.current_pid == 0)
    {
        ft_putendl_fd(line, 0);
        exit(0);
    }
}


int ft_count(t_tokens *begin, t_tokens *finish)
{
    int count;
    count = 0;

    while (begin != finish)
    {
        if (begin->type == 0)
            count++;
        begin = begin->next;
    }
    return(count);
}

char **prepere_argv(t_tokens *begin,t_tokens *finish)
{
    char **argv;
    int count;
    int i ;
    
    i=0;
    count = ft_count(begin,finish);
    if(!(argv = (char **)malloc(sizeof(char*) * (count + 1))))
        return(0);
    while (begin != finish)
    {
        if(begin->type == 0)
        {
            argv[i] = ft_strdup(begin->data);
            i++;
        }
        begin = begin->next;
    }
    argv[i] = NULL;
    return(argv);
}

int authorization_re(t_tokens *token)
{
    int i_data;
    char *s_data; 
    
    s_data = NULL;
    i_data = ft_atoi(token->data);
    s_data = ft_itoa(i_data);
   
   
    // if (ft_strcmp(token->data, "-") == 0)
    //     dprintf(2,"tokens->data = %s\n", token->data);
    if (ft_strcmp(token->data, s_data) == 0)
    {
        if(i_data >= 0 && i_data <= 2)
        {
            if (ft_strcmp(token->data, "0") == 0)
                return(1);
            else if (ft_strcmp(token->data, "1") == 0)
                return(1);
            else if (ft_strcmp(token->data, "2") == 0)
                return(1);
        }
    }
    return(0);
}

void redirection(t_tokens *begin, t_tokens *finish)
{
    while(begin != finish)
    {
        if (authorization_re(begin) == 1 && begin->next != NULL 
        && begin->next->type == REDIRECTION_RIGHT_AGGREGATION)
        {
            if (begin->next->next->data != NULL)
                redirection_out(begin->next->next->data);
        }
        else if(begin->type == REDIRECTION_RIGHT)
            redirection_out(begin->next->data);
        else if(begin->type == REDIRECTION_LEFT)
            redirection_in(begin->next->data);
        else if (begin->type == REDIRECTION_RIGHT_RIGHT)
            redirection_out_out(begin->next->data);
        else if (begin->type == REDIRECTION_LEFT_LEFT)
            ft_heredoc(begin->next->data);
        else if (begin->type == REDIRECTION_LEFT_LEFT_LEFT)
            ft_herestr(begin->next->data);
        else if (begin->type == REDIRECTION_RIGHT_AGGREGATION)
        {
            if (begin->next != NULL && authorization_re(begin->next) == 1)
                dup(WRITE_END);
            else 
                redirection_out(begin->next->data);
        }
        else if (begin->type == REDIRECTION_LEFT_AGGREGATION)
			if (begin->next != NULL && authorization_re(begin->next) == 1)
				dup(WRITE_END);
		begin = begin->next;
	}
}
