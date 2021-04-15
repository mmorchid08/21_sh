/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:24:55 by mmorchid          #+#    #+#             */
/*   Updated: 2021/04/11 17:35:09 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

int		ft_check_builtins(char *table)
{
	if (table)
	{
		if (ft_strcmp(table, "echo") == 0)
			return (1);
		if (ft_strcmp(table, "cd") == 0)
			return (1);
		if (ft_strcmp(table, "setenv") == 0)
			return (1);
		if (ft_strcmp(table, "unsetenv") == 0)
			return (1);
		if (ft_strcmp(table, "env") == 0)
			return (1);
		if (ft_strcmp(table, "exit") == 0)
			return (1);
		if (ft_strcmp(table, "alias") == 0)
			return (1);
		if (ft_strcmp(table, "unalias") == 0)
			return (1);
		if (ft_strcmp(table, "hash") == 0)
			return (1);
		if (ft_strcmp(table, "test") == 0)
			return (1);
	}
	return (0);
}

void	ft_verify_non_fork_builtins(t_tokens *token_begin)
{
	if (ft_strcmp(token_begin->data, "cd") == 0)
		ft_operation_non_fork_cd(token_begin->args);
	else if (ft_strcmp(token_begin->data, "setenv") == 0
			&& token_begin->args->next != NULL)
		ft_add_change_env(token_begin->args);
	else if (ft_strcmp(token_begin->data, "unsetenv") == 0
			&& token_begin->args->next != NULL)
		ft_delete_one_env(token_begin->args);
	else if (ft_strcmp(token_begin->data, "alias") == 0 && token_begin->args->next != NULL)
		ft_operation_non_fork_alias(token_begin->args);
	else if (ft_strcmp(token_begin->data, "unalias") == 0
			&& token_begin->args->next != NULL)
		ft_operation_non_fork_unalias(token_begin->args);
	else if (ft_strcmp(token_begin->data, "exit") == 0)
		ft_exec_exit();
}

void	ft_verify_builtins(t_tokens *token_begin)
{
	int test_ret = 0;
	
	if (ft_strcmp(token_begin->data, "echo") == 0)
		ft_operation_echo(token_begin->args);
	else if (ft_strcmp(token_begin->data, "cd") == 0)
		ft_operation_cd(token_begin->args);
	else if (ft_strcmp(token_begin->data, "setenv") == 0
			&& token_begin->args->next == NULL)
		ft_env_function();
	else if (ft_strcmp(token_begin->data, "unsetenv") == 0
			&& token_begin->args->next == NULL)
		ft_putendl("unsetenv: not enough arguments");
	else if (ft_strcmp(token_begin->data, "alias") == 0 && token_begin->args->next == NULL)
		ft_list_alias(g_env.al);
	else if (ft_strcmp(token_begin->data, "unalias") == 0
			&& token_begin->args->next == NULL)
		ft_putendl("unalias: not enough arguments");
	else if (ft_strcmp(token_begin->data, "env") == 0)
		ft_env_function();
	else if (ft_strcmp(token_begin->data, "test") == 0)
		test_ret = test_commade(token_begin);

}
