/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_sequel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:12:03 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/23 16:59:40 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

char	*ft_get_home(void)
{
	char		*home;
	t_var	*tmp;

	tmp = g_env.var;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
			home = tmp->value;
		tmp = tmp->next;
	}
	return (home);
}

char	*ft_get_pwd(void)
{
	char		*pwd;
	t_var		*tmp;

	tmp = g_env.var;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			pwd = tmp->value;
		tmp = tmp->next;
	}
	return (pwd);
}

char	*ft_get_old_pwd(void)
{
	char		*old_pwd;
	t_var		*tmp;

	tmp = g_env.var;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			old_pwd = tmp->value;
		tmp = tmp->next;
	}
	return (old_pwd);
}

void	ft_tack_pwd(void)
{
	t_var	*tmp;

	tmp = g_env.var;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = getcwd(NULL, 1024);
			break ;
		}
		tmp = tmp->next;
	}
}
