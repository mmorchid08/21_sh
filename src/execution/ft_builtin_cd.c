/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:55:38 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 15:48:27 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_setenv_var(t_var **var, char *key, char *value)
{
	t_var *tmp;

	tmp = *var;
	while (tmp)
	{
		if (ft_strequ(key, tmp->key))
		{
			free(tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_env_var(var, ft_new_env_var(ft_strdup(key), value));
}

int		ft_cd_ret_err(char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) != 0)
		return (1);
	if (!S_ISDIR(path_stat.st_mode))
		return (3);
	if (access(path, R_OK))
		return (2);
	return (0);
}

void	ft_operation_non_fork_cd(t_tokens *line)
{
	char *path;

	path = (line->next) ? line->next->data : NULL;
	if (path && ft_strequ(path, "-"))
	{
		path = ft_get_var_value(g_env.var, "OLDPWD");
		path = (path) ? path : g_env.working_dir;
		free(line->next->data);
		line->next->data = ft_strdup(path);
	}
	if (!(line->ret = ft_getcwd((path) ? path : g_env.home)))
	{
		chdir(g_env.working_dir);
		ft_setenv_var(&(g_env.var), "PWD", ft_strdup(g_env.working_dir));
		ft_setenv_var(&(g_env.var), "OLDPWD",
		ft_strdup(g_env.old_working_dir));
		line->status = 1;
		return ;
	}
}

void	ft_operation_cd(t_tokens *line)
{
	t_tokens *path;

	if (!line->status)
	{
		path = line->next;
		if (line->ret == 2)
			ft_putstr_fd("cd: Permission denied: ", 2);
		else if (line->ret == 1)
			ft_putstr_fd("cd: No such file or directory: ", 2);
		else
			ft_putstr_fd("cd: Not a directory: ", 2);
		if (path && ft_strequ(path->data, "-") && g_env.old_working_dir)
			ft_putstr_fd(g_env.old_working_dir, 2);
		else if (path)
			ft_putstr_fd(path->data, 2);
		ft_putendl_fd("", 2);
	}
}
