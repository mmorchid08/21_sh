/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:58:41 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/21 13:19:38 by mmorchid         ###   ########.fr       */
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

int		ft_check_fd_sequel(int count, int data, t_tokens *tmp)
{
	if (tmp->next == NULL)
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
	return (0);
}

int		ft_check_fd(t_tokens *tmp)
{
	int	data;
	int	count;

	count = 0;
	while (tmp)
	{
		if (tmp->type == REDIRECTION_LEFT && (!tmp->next ||
					!tmp->next->data ||
					ft_read_red_err(tmp->next->data, tmp->type)))
			return (1);
		if ((tmp->type == REDIRECTION_RIGHT ||
					tmp->type == REDIRECTION_RIGHT_RIGHT) &&
				(!tmp->next || !tmp->next->data
				|| ft_write_red_err(tmp->next->data, tmp->type)))
			return (1);
		if (tmp->type == REDIRECTION_RIGHT_AGGREGATION
				|| tmp->type == REDIRECTION_LEFT_AGGREGATION)
			if (ft_check_fd_sequel(count, data, tmp) == 1)
				return (1);
		count++;
		tmp = tmp->next;
	}
	return (0);
}
