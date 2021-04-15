/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:08:23 by mmorchid          #+#    #+#             */
/*   Updated: 2021/04/10 12:18:34 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

t_flags ft_tak_flags(t_tokens *token_args, t_flags *flags)
{
    int     i;
    int     j;
    char    *num;

    j = 0;
    while (token_args)
    {
        if (token_args->data[0] == '-' && !ft_isdigit(token_args->data[1]))
        {
            i = 1;
            while (token_args->data[i])
            {
                if (token_args->data[i] != 'l' && token_args->data[i] != 'e'\
                && token_args->data[i] != 'r' && token_args->data[i] != 's'\
                && token_args->data[i] != 'n')
                {
                    ft_putstr_fd("fc: bad option: -",2);
                    ft_putchar_fd(token_args->data[i],2);
                    ft_putendl_fd("",2);
                    flags->error = 1;
                    break ;
                }
                else if (token_args->data[i] == 'l')
                    flags->l = 1;
                else if (token_args->data[i] == 'e')
                    flags->e = 1;
                else if (token_args->data[i] == 'r')
                    flags->r = 1;
                else if (token_args->data[i] == 's')
                    flags->s = 1;
                else if (token_args->data[i] == 'n')
                    flags->n = 1;
                i++;
            }
        }
        else
        {
            if (token_args->data[0] == '-')
                j++;
            while (token_args->data[j] != ' ' && ft_isdigit(token_args->data[j]))
                j++;
            num = ft_strsub(token_args->data,0,j);
            if (flags->first_num == 0)
                flags->first_num = ft_atoi(num);
            else if (flags->last_num == 0)
                flags->last_num = ft_atoi(num);
            free(num);        
            
        }
        token_args = token_args->next;
    }
   return (*flags);
}

void ft_init_flags(t_flags *flags)
{
    flags->e = 0;
    flags->l = 0;
    flags->s = 0;
    flags->n = 0;
    flags->r = 0;
    flags->error = 0;
    flags->first_num = 0;
    flags->last_num = 0;
}

void    ft_list_his_l(t_his *his, int counter)
{
    while (his && his->prev)
    {
        ft_putnbr_fd(counter++,1);
        ft_putendl_fd(his->line,1);
        his = his->prev;
    }
}

int ft_count_list_his(t_his *his)
{
    int counter;
    
    counter = 1;
    while (his)
    {
        counter++;
        his = his->next;    
    }
    return(counter);
}

void ft_write_hid_lr(t_his **his, int counter_his, t_flags flags)
{
    int counter;
    
    counter = flags.first_num == 0 ? counter_his - 16 : flags.first_num;
    counter_his = flags.last_num != 0  ? flags.last_num : counter_his;
    
    while (counter_his >= counter && (*his) && (*his)->next)
    {
        if(flags.n == 0)
        {
            ft_putstr_fd("    ",1);
            ft_putnbr_fd(counter_his--,1);
            ft_putstr_fd("  ",1);
        }
        else
            counter_his--;
       ft_putendl_fd((*his)->line,1);
        if (flags.last_num != 0)
        {
            if (flags.last_num == flags.first_num)
                break;
            flags.last_num-- ;    
        }
       (*his) = (*his)->next;
    }
}

void    ft_begin_finish(t_flags flags,t_befi *distance, int counter_his)
{
    if (flags.first_num == 0 && flags.last_num == 0)
    {
        distance->begin = counter_his - 16;
        distance->finish = counter_his;
    }    
    if (flags.first_num < flags.last_num && (flags.first_num > 0 && flags.last_num > 0))
    {
        //we talk about go next and back with prev
        distance->begin = flags.first_num;
        distance->finish = flags.last_num;
    }
    else if (flags.first_num > flags.last_num && (flags.first_num > 0 && flags.last_num > 0))
    {
        distance->begin = flags.last_num;
        distance->finish = flags.first_num;
    }
    else if ((flags.first_num < 0 || flags.last_num < 0))
    {
        if (flags.first_num < 0)
        {
            distance->begin = counter_his + flags.first_num;
        }   
        else
        {
            distance->begin = flags.first_num;
        }
        if(flags.last_num < 0)
        {
            distance->finish = counter_his + flags.last_num;
        }
        else
        {
               distance->finish =  flags.last_num;
        }
    }
    
}

void ft_write_hid_l(t_his *his, int counter_his, t_flags flags, t_befi dis)
{
    int i;

    i = -1;
    printf("--------------\n");
    printf("dis.begin = %d\n", dis.begin);
    while (his && his->next && i < dis.begin)
    {
        printf("data_prev ---> %s\n", his->line);
        his = his->next;
    }
    // while (his && his->prev)
    // {
    //     if (flags.n == 0)
    //     {
    //         ft_putstr_fd("    ",1);
    //         ft_putnbr_fd(counter++,1);
    //         ft_putstr_fd("  ",1);
    //     }
    //     ft_putendl_fd(his->line,1);
    //     if (flags.last_num != 0)
    //     {
    //         if (flags.first_num == flags.last_num)
    //             break;
    //         flags.first_num++ ;    
    //     }
    //     his = his->prev;
    // }
}

// counter_his - (last one ) + 2;
void ft_fc_command(t_tokens *token_args)
{
    t_tokens *args;
    t_flags flags;
    t_his *his;
    t_befi distance;

    int i;
    int counter_his;
    int begin;
    
    args = token_args->args;
    his = g_env.his;
    i = -1;
    distance.begin = 0;
    distance.finish = 0;

    counter_his = ft_count_list_his(his);
    printf("counter his ----> %d\n", counter_his);
    
    ft_init_flags(&flags);
    begin  = 16;
    if (args->next != NULL)
    {
        args = args->next;
        flags = ft_tak_flags(args, &flags);
    }
    printf("first = %d last = %d\n", flags.first_num, flags.last_num);
    ft_begin_finish(flags, &distance,counter_his);
    printf("distance.begin =%d ---- distance.finish =%d\n", distance.begin, distance.finish);
    //--------tal lhena mzyne
    
    if(flags.error == 0)
    {
        // if (flags.first_num != 0)
        //     begin = counter_his + 1 - flags.first_num;
        // if ((flags.l == 1 && flags.r == 1) || flags.first_num > flags.last_num)
        //     ft_write_hid_lr(&his, counter_his, flags);
            
        // while (++i < begin && his && his->next)
        //     his = his->next;
        
        if (flags.l == 1 && flags.r == 0)
            ft_write_hid_l(his, counter_his, flags, distance); 
    }
}

/*
void ft_write_hid_lr(t_his **his, int counter_his, t_flags flags)
{
    int counter;
    
    counter = flags.first_num == 0 ? counter_his - 16 : flags.first_num;
    counter_his = flags.last_num != 0  ? flags.last_num : counter_his;
    
    while (counter_his >= counter && (*his) && (*his)->next)
    {
        if(flags.n == 0)
        {
            ft_putstr_fd("    ",1);
            ft_putnbr_fd(counter_his--,1);
            ft_putstr_fd("  ",1);
        }
        else
            counter_his--;
       ft_putendl_fd((*his)->line,1);
        if (flags.last_num != 0)
        {
            if (flags.last_num == flags.first_num)
                break;
            flags.last_num-- ;    
        }
       (*his) = (*his)->next;
    }
}


////////////////
    void ft_write_hid_l(t_his **his, int counter_his, t_flags flags)
{
    int counter;

    printf("first = %d ---------- last = %d\n", flags.first_num , flags.last_num);
    counter = flags.first_num == 0 ? counter_his - 15 : flags.first_num;
    while ((*his) && (*his)->prev)
    {
        if (flags.n == 0)
        {
            ft_putstr_fd("    ",1);
            ft_putnbr_fd(counter++,1);
            ft_putstr_fd("  ",1);
        }
        ft_putendl_fd((*his)->line,1);
        if (flags.last_num != 0)
        {
            if (flags.first_num == flags.last_num)
                break;
            flags.first_num++ ;    
        }
        (*his) = (*his)->prev;
    }
}
*/