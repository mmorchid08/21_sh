/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:52:46 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/24 17:52:13 by mmorchid         ###   ########.fr       */
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

void redirection_in_in(char *file_name) /*    <<   */
{
    int in_in = open(file_name, O_WRONLY | O_APPEND);
    dup2(in_in,READ_END);
    close(in_in);
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
    while(begin!= finish)
    {
        if(begin->type == REDIRECTION_RIGHT)
            redirection_out(begin->next->data);
        else if(begin->type == REDIRECTION_LEFT)
            redirection_in(begin->next->data);
        else if (begin->type == REDIRECTION_RIGHT_RIGHT)
            redirection_out_out(begin->next->data);
        else if (begin->type == REDIRECTION_LEFT_LEFT)
            redirection_in_in(begin->next->data);
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
