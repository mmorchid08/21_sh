/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 20:39:23 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/10 20:44:10 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_get_git_branch_2(int fd)
{
	char	*line;
	char	*tmp;
	int		ret;

	if ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((tmp = ft_strrchr(line, '/')) && *(tmp + 1))
		{
			g_env.branch = ft_free_strjoin(
					ft_strdup(C_BLU" ("C_YEL), ft_strjoin("⎇ :", tmp + 1));
			g_env.branch = ft_free_strjoin(g_env.branch, ft_strdup(C_BLU")"));
			g_env.branch_len = ft_strlen(tmp + 1) + 6;
		}
		else
		{
			if (ft_strlen(line) > 9)
				line[8] = '\0';
			g_env.branch_len = ft_strlen(line) + 6;
			g_env.branch = ft_free_strjoin(
					ft_strdup(C_BLU" ("C_YEL), ft_strjoin("⎇ :", line));
			g_env.branch = ft_free_strjoin(g_env.branch, ft_strdup(C_BLU")"));
		}
	}
	(ret == -1) ? exit(1) : 1;
	ft_strdel(&line);
}

void	ft_get_git_branch(char *pwd)
{
	struct stat	st;
	int			fd;
	char		*path;

	path = ft_strjoin(pwd, "/./.git/HEAD");
	g_env.branch_len = 0;
	if (lstat(path, &st) != -1 && access(path, R_OK))
	{
		fd = open(path, O_RDONLY);
		if (g_env.branch)
			ft_strdel(&(g_env.branch));
		ft_get_git_branch_2(fd);
		if (g_env.gnl)
			ft_strdel(&(g_env.gnl));
		close(fd);
	}
	else if (g_env.branch)
		ft_strdel(&g_env.branch);
	free(path);
}
