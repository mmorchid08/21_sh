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

char	*ft_get_home(t_list_env *env_list)
{
	char		*home;
	t_list_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
			home = tmp->value;
		tmp = tmp->next;
	}
	return (home);
}

char	*ft_get_pwd(t_list_env *list_env)
{
	char		*pwd;
	t_list_env	*tmp;

	tmp = list_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			pwd = tmp->value;
		tmp = tmp->next;
	}
	return (pwd);
}

char	*ft_get_old_pwd(t_list_env *list_env)
{
	char		*old_pwd;
	t_list_env	*tmp;

	tmp = list_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			old_pwd = tmp->value;
		tmp = tmp->next;
	}
	return (old_pwd);
}

void	ft_tack_pwd(t_list_env *env_list)
{
	t_list_env	*tmp;

	tmp = env_list;
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
