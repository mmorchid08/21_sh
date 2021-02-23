/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:24:55 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/23 16:50:40 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int	ft_chek_builtins(char *tab)
{
	if (tab)
	{
		if (ft_strcmp(tab, "echo") == 0)
			return (1);
		if (ft_strcmp(tab, "cd") == 0)
			return (1);
		if (ft_strcmp(tab, "setenv") == 0)
			return (1);
		if (ft_strcmp(tab, "unsetenv") == 0)
			return (1);
		if (ft_strcmp(tab, "env") == 0)
			return (1);
		if (ft_strcmp(tab, "exit") == 0)
			return (1);
	}
	return (0);
}

void	ft_verify_builtins(t_tokens *token_begin,
t_tokens *token_finish, t_list_env *list_env)
{
	if (ft_strcmp(token_begin->data, "echo") == 0)
		ft_operation_echo(token_begin, token_finish);
	else if (ft_strcmp(token_begin->data, "cd") == 0)
		ft_operation_cd(token_begin, token_finish, list_env);
	else if (ft_strcmp(token_begin->data, "setenv") == 0)
		token_begin->next == NULL ? ft_env_function(list_env)
			: ft_add_change_env(token_begin, token_finish, list_env);
	else if (ft_strcmp(token_begin->data, "unsetenv") == 0)
	{
		if (token_begin->next == NULL)
			ft_putendl("unsetenv: not enough arguments");
		else
			ft_delete_one_env(&list_env, token_begin, token_finish);
	}
	else if (ft_strcmp(token_begin->data, "env") == 0)
		ft_env_function(list_env);
	else if (ft_strcmp(token_begin->data, "exit") == 0)
	{
		free_list_env(&list_env);
		exit(0);
	}
}
