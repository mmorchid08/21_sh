/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:25:07 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/23 16:59:03 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_tilda(t_list_env *list_env, char *value, int len)
{
	char		*old_pwd;
	t_list_env	*tmp;
	char		*poit;
	int			i;

	i = 0;
	tmp = list_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			old_pwd = tmp->value;
		tmp = tmp->next;
	}
	poit = ft_strsub(value, len, ft_strlen(value));
	old_pwd = ft_strjoin("~", poit);
	free(poit);
	while (old_pwd[i])
		write(1, &old_pwd[i++], 1);
	write(1, "\n", 1);
	free(old_pwd);
}

void	ft_write_path(t_list_env *list_env, char *value)
{
	char		*home;
	t_list_env	*tmp;
	int			len;

	home = ft_get_home(list_env);
	len = (int)ft_strlen(home);
	tmp = list_env;
	if (ft_strncmp(home, value, len) == 0)
		ft_tilda(list_env, value, len);
	else if (ft_strcmp(value, "/") == 0)
	{
		write(1, "/", 1);
		write(1, "\n", 1);
	}
}

void	ft_work_hyphen(t_list_env *list_env, char *token)
{
	char		*home;
	char		*pwd;
	char		*old_pwd;
	t_list_env	*tmp;

	tmp = list_env;
	home = ft_get_home(list_env);
	pwd = ft_get_pwd(list_env);
	old_pwd = ft_get_old_pwd(list_env);
	if (ft_strcmp(token, "-") == 0)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "PWD") == 0)
			{
				tmp->value = old_pwd;
				chdir(tmp->value);
				ft_write_path(list_env, tmp->value);
			}
			else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
				tmp->value = pwd;
			tmp = tmp->next;
		}
	}
}

void	ft_the_current(t_list_env *list_env, char *path)
{
	t_list_env	*tmp;

	tmp = list_env;
	ft_tack_pwd(list_env);
	chdir(path);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = getcwd(NULL, 1024);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_operation_cd(t_tokens *token_begin, t_tokens *token_finish, t_list_env *list_env)
{
	int			lst;
	struct stat	buf;
	t_list_env	*tmp;
	t_tokens	*cp;
	int			count;

	count = 0;
	tmp = list_env;
	cp = token_begin;
	while (cp != token_finish && cp->type == 0)
	{
		count++;
		cp = cp->next;
	}
	if (count >= 3)
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(token_begin->next->data);
	}
	if (count == 1)
		ft_the_current(list_env, ft_get_home(list_env));
	if (count == 2)
	{
		lst = lstat(token_begin->next->data, &buf);
		if (ft_strcmp(token_begin->next->data, "-") == 0)
			ft_work_hyphen(list_env, token_begin->next->data);
		else if (S_ISDIR(buf.st_mode))
			ft_the_current(list_env, token_begin->next->data);
		else
		{
			ft_putstr("cd : not directory : ");
			ft_putendl(token_begin->next->data);
		}
	}
}
