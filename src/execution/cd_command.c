/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:25:07 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/18 15:02:09 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_tilda(char *value, int len)
{
	char		*old_pwd;
	t_var		*tmp;
	char		*poit;
	int			i;

	i = 0;
	tmp = g_env.var;
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

void	ft_write_path(char *value)
{
	char		*home;
	int			len;

	home = ft_get_home();
	len = (int)ft_strlen(home);
	if (ft_strncmp(home, value, len) == 0)
		ft_tilda(value, len);
	else if (ft_strcmp(value, "/") == 0)
	{
		write(1, "/", 1);
		write(1, "\n", 1);
	}
}

void	ft_work_hyphen(char *token)
{
	char		*pwd;
	char		*old_pwd;
	t_var		*tmp;

	tmp = g_env.var;
	pwd = ft_get_pwd();
	old_pwd = ft_get_old_pwd();
	if (ft_strcmp(token, "-") == 0)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "PWD") == 0)
			{
				tmp->value = old_pwd;
				chdir(tmp->value);
				ft_write_path(tmp->value);
			}
			else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
				tmp->value = pwd;
			tmp = tmp->next;
		}
	}
}

void	ft_the_current(char *path)
{
	t_var	*tmp;

	tmp = g_env.var;
	ft_tack_pwd();
	chdir(path);
	dprintf(2, "path = %s\n", path);
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

void	ft_operation_non_fork_cd(t_tokens *token_begin)
{
	struct stat	buf;
	t_tokens	*cp;
	int			count;

	count = 0;
	cp = token_begin;
	while (cp)
	{
		count++;
		cp = cp->next;
	}
	if (count >= 3)
		token_begin->next->status = 0;
	if (count == 1)
		ft_the_current(ft_get_home());
	if (count == 2)
	{
		if (lstat(token_begin->next->data, &buf) == -1)
		{
			perror("lstat");
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(token_begin->next->data, "-") == 0)
			ft_work_hyphen(token_begin->next->data);
		else if (S_ISDIR(buf.st_mode))
			ft_the_current(token_begin->next->data);
		else if (S_ISLNK(buf.st_mode))
		{
			//is linkhre 
		}
		else
			token_begin->next->status = 0;
	}
}

void	ft_operation_cd(t_tokens *token_begin)
{
	struct		stat	buf;
	t_tokens	*cp;
	int			count;

	count = 0;
	cp = token_begin;
	while (cp)
	{
		count++;
		cp = cp->next;
	}
	if (count >= 3)
	{
		ft_putstr("cd: String not in pwd: ");
		ft_putendl(token_begin->next->data);
	}
	if (count == 2)
	{
		if (token_begin->next->status == 0)
		{
			ft_putstr_fd("cd : Not directory : ", 2);
			ft_putendl_fd(token_begin->next->data, 2);
		}
	}
}
