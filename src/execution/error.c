/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:33:00 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/28 16:27:54 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_check_error(char *name)
{
	ft_putstr_fd("21sh : Command not fount : ", 2);
	ft_putendl_fd(name, 2);
}

int		ft_know_type(int type)
{
	if (type == 1 || type == 2 || type == 3
			|| type == 4 || type == 5 || type == 6 || type == 7
			|| type == 8 || type == 9 || type == 10
			|| type == 12)
		return (1);
	return (0);
}

int		err_pars(t_tokens *tmp)
{
	if (tmp->type != WORD)
	{
		ft_putstr_fd("21sh: parse error near `", 2);
		ft_putstr_fd(tmp->data, 2);
		ft_putendl_fd("'", 2);
		return (1);
	}
	if (!tmp->next)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->type != WORD && !check_red(tmp->type))
	{
		ft_putstr_fd("21sh: parse error near `", 2);
		ft_putstr_fd(tmp->data, 2);
		ft_putendl_fd("'", 2);
		return (1);
	}
	return (0);
}

int		ft_checksemi(t_tokens *tmp)
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

int		ft_read_red_err(char *path, int type)
{
	struct stat path_stat;

	if (stat(path, &path_stat) != 0)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": File not found", 2);
		return (1);
	}
	if (access(path, R_OK))
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
