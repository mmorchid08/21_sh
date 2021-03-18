/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:33:00 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/18 13:01:34 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_check_error(char *name)
{
	ft_putstr_fd("21sh : Command not fount : ", 2);
	ft_putendl_fd(name, 2);
}

int	ft_know_type(int type)
{
	if (type == 1 || type == 2 || type == 3
		|| type == 4 || type == 5 || type == 6 || type == 7
		|| type == 8 || type == 9 || type == 10
		 || type == 12)
		return (1);
	return (0);
}

int	ft_error_parse(t_tokens *tmp)
{
	while (tmp)
	{
		if (ft_know_type(tmp->type) == 1)
		{
			if (tmp->next != NULL && ft_know_type(tmp->next->type) == 1)
			{
				ft_putstr_fd("21sh: parse error near `", 2);
				ft_putstr_fd(tmp->next->data, 2);
				ft_putendl_fd("'", 2);
				return (1);
			}
		
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_multi_semi(t_tokens *tmp)
{
	while (tmp)
	{
		if (tmp->type == SEMICOLON)
		{
			if (tmp->next != NULL && tmp->next->type == SEMICOLON)
			{
				ft_putendl_fd("21sh: parse error near `;;'", 2);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int     ft_read_red_err(char *path, int type)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0)
    {
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": File not found", 2);
		return (1);
	}
	if (access(path, R_OK) || access(path, X_OK))
    {
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
    if (!S_ISREG(path_stat.st_mode))
    {
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is not a file", 2);
		return (1);
	}
    return (0);
}

int     ft_write_red_err(char *path, int type)
{
    struct stat path_stat;
	int ret;

	ret = stat(path, &path_stat);

	if (!ret && access(path, W_OK))
    {
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
    if (!ret && !S_ISREG(path_stat.st_mode))
    {
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is not a file", 2);
		return (1);
	}
    return (0);
}

int	ft_check_bad_fd(t_tokens *tmp)
{
	int	data;
	int count;

	count  = 0;

	while (tmp)
	{
		if (tmp->type == REDIRECTION_LEFT && (!tmp->next || !tmp->next->data || ft_read_red_err(tmp->next->data, tmp->type)))
			return (1);
		if ((tmp->type == REDIRECTION_RIGHT || tmp->type == REDIRECTION_RIGHT_RIGHT) && (!tmp->next || !tmp->next->data || ft_write_red_err(tmp->next->data, tmp->type)))
			return (1);
		if (tmp->type == REDIRECTION_RIGHT_AGGREGATION
			|| tmp->type == REDIRECTION_LEFT_AGGREGATION)
		{
			printf("*********\n");
			if (tmp->next == NULL && count != 0)
			{
				ft_putendl_fd("21sh: Parse error near `\\n'", 2);
				return (1);
			}
			if (tmp->next == NULL && count == 0)
			{
				data = ft_atoi(tmp->next->data);
				if (data > 2)
				{
					ft_putstr_fd("21sh: ", 2);
					ft_putnbr_fd(data, 2);
					ft_putendl_fd(": Bad file descriptor", 2);
					return (1);
				}
			}
			// if (tmp->next != NULL && tmp->next->type == REDIRECTION_WORD)
			// {
			// 	printf("///////////////////////\n");
			// 	data = ft_atoi(tmp->next->data);
			// 	if (data > 2)
			// 	{
			// 		ft_putstr_fd("21sh: ", 2);
			// 		ft_putnbr_fd(data, 2);
			// 		ft_putendl_fd(": bad file descriptor", 2);
			// 		return (1);
			// 	}
			// }
		}
		count ++;
		tmp = tmp->next;
	}
	return (0);
}
