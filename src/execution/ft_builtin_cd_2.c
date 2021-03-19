/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:55:38 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:55:39 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_free_path_list(t_path **path)
{
	t_path *tmp;

	while ((*path))
	{
		tmp = (*path)->next;
		ft_free_path(path);
		(*path) = tmp;
	}
}

void	ft_getcwd_c1(t_path *arg, t_path **pwd, char **wd)
{
	*wd = ft_join_path(*pwd);
	while (arg)
	{
		if (ft_strequ("..", arg->line))
		{
			if (!ft_strequ(*wd, "/"))
				ft_remove_last_path(pwd);
			else
			{
				free(arg->line);
				arg->line = ft_strdup("/");
			}
		}
		else if (!ft_strequ(".", arg->line))
			ft_pushback_path(pwd, ft_new_path(ft_strdup(arg->line)));
		if (*wd)
			free(*wd);
		*wd = ft_join_path(*pwd);
		arg = arg->next;
	}
}

void	ft_getcwd_c2(char **wd, char *path)
{
	t_path	*pwd;
	t_path	*arg;

	pwd = NULL;
	arg = NULL;
	ft_populate_path_list(&pwd,
	ft_strsplit((*path == '/') ? "/" : g_env.working_dir, '/'), 1);
	ft_populate_path_list(&arg, ft_strsplit(path, '/'), 1);
	ft_getcwd_c1(arg, &pwd, wd);
	ft_free_path_list(&arg);
	ft_free_path_list(&pwd);
}

int		ft_getcwd(char *path)
{
	char	*wd;
	int		ret;

	wd = NULL;
	if ((ret = 1) && path)
		ft_getcwd_c2(&wd, path);
	if (wd && (ret = ft_cd_ret_err(wd)) == 0)
	{
		(g_env.old_working_dir) ? ft_strdel(&(g_env.old_working_dir)) : 1;
		g_env.old_working_dir = ft_strdup(g_env.working_dir);
		ft_strdel(&(g_env.working_dir));
		g_env.working_dir = wd;
	}
	else if (wd)
		free(wd);
	return (ret);
}
