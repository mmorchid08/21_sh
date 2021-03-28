/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:58:41 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/28 13:31:20 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int		ft_write_red_err(char *path, int type)
{
	struct stat	path_stat;
	int			ret;

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

int		ft_check_fd_sequel(t_tokens *tmp)
{
	char str[10];

	if (tmp->pre_fd > -1 && read(tmp->pre_fd, (void *)str, 0) < 0)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putnbr_fd(tmp->pre_fd, 2);
		ft_putendl_fd(": Bad file descriptor", 2);
		return (1);
	}
	if (tmp->sub_fd > -1 && read(tmp->sub_fd, (void *)str, 0) < 0)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putnbr_fd(tmp->sub_fd, 2);
		ft_putendl_fd(": Bad file descriptor", 2);
		return (1);
	}
	return (0);
}

int		ft_check_fd(t_tokens *tmp)
{
	while (tmp)
	{
		if (check_red(tmp->type) &&
				!(tmp->type == REDIRECTION_RIGHT_AGGREGATION) &&
				!(tmp->type == REDIRECTION_LEFT_AGGREGATION) && !tmp->filename)
		{
			ft_putendl_fd("21sh: parse error", 2);
			return (1);
		}
		if (tmp->type == REDIRECTION_LEFT &&
				ft_read_red_err(tmp->filename, tmp->type))
			return (1);
		if ((tmp->type == REDIRECTION_RIGHT ||
					tmp->type == REDIRECTION_RIGHT_RIGHT)
				&& ft_write_red_err(tmp->filename, tmp->type))
			return (1);
		if (check_red(tmp->type) && ft_check_fd_sequel(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
