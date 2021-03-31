/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:58:41 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/31 17:20:00 by mmorchid         ###   ########.fr       */
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

int		ft_check_fd(t_tokens *tmp)
{
	if (check_red(tmp->type) && !tmp->filename)
	{
		ft_putendl_fd("21sh: Parse error", 2);
		return (1);
	}
	if (tmp->type == REDIRECTION_LEFT &&
			ft_read_red_err(tmp->filename, tmp->type))
		return (1);
	if ((tmp->type == REDIRECTION_RIGHT ||
				tmp->type == REDIRECTION_RIGHT_RIGHT)
			&& ft_write_red_err(tmp->filename, tmp->type))
		return (1);
	return (0);
}
