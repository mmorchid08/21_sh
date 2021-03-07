/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:33:00 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/28 19:03:06 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_check_error(char *name)
{
	ft_putstr_fd("21sh : command not fount : ", 2);
	ft_putendl_fd(name, 2);
}

int	ft_know_type(t_tokens *tmp)
{
	if (tmp->type == 1 || tmp->type == 2 || tmp->type == 3
		|| tmp->type == 4 || tmp->type == 5 || tmp->type == 6
		|| tmp->type == 8 || tmp->type == 9 || tmp->type == 10
		||tmp->type == 11 || tmp->type == 12)
		return (1);
	return (0);
}

int	ft_error_parse(t_tokens *tmp)
{
	while (tmp)
	{
		if (ft_know_type(tmp) == 1)
		{
			if (tmp->type == REDIRECTION_LEFT_AGGREGATION
				&& authorization_re(tmp) == 0)
			{
				ft_putendl_fd("21sh: file number expected", 2);
				return (1);
			}
			else if (tmp->next != NULL && ft_know_type(tmp->next) == 1)
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

int     ft_exe_ret_err(char *path, int type)
{
    struct stat path_stat;
    if (type == REDIRECTION_LEFT && stat(path, &path_stat) != 0)
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
		ft_putendl_fd(": File is not a directory", 2);
		return (1);
	}
    return (0);
}

int	ft_check_bad_fd(t_tokens *tmp)
{
	int	data;

	while (tmp)
	{
		if (tmp->type == REDIRECTION_RIGHT ||
		tmp->type == REDIRECTION_LEFT ||
		tmp->type == REDIRECTION_RIGHT_RIGHT)
		{
			if (!tmp->next || !tmp->next->data || ft_exe_ret_err(tmp->next->data, tmp->type))
				return (1);
		}
		if (tmp->type == REDIRECTION_RIGHT_AGGREGATION
			|| tmp->type == REDIRECTION_LEFT_AGGREGATION)
		{
			if (tmp->next == NULL)
			{
				ft_putendl_fd("21sh: parse error near `\\n'", 2);
				return (1);
			}
			if (tmp->next != NULL && tmp->next->type == REDIRECTION_WORD)
			{
				data = ft_atoi(tmp->next->data);
				if (data > 2)
				{
					ft_putstr_fd("21sh: ", 2);
					ft_putnbr_fd(data, 2);
					ft_putendl_fd(": bad file descriptor", 2);
					return (1);
				}
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
