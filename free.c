/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_semi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:33:00 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/12 18:54:33 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_free_table(char ***tab)
{
	int i;

	i = -1;
	while ((*tab)[++i])
		free((*tab)[i]);
	free((*tab));
}

// void	free_list_token(t_tokens **token)
// {
// 	t_tokens	*current;
// 	t_tokens	*next;

// 	current = *token;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->token);
// 		free(current);
// 		current = next;
// 	}
// 	*token = NULL;
// }

// void	free_list_env(t_list_env **env)
// {
// 	t_list_env	*current;
// 	t_list_env	*next;

// 	current = *env;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->key);
// 		free(current->value);
// 		free(current);
// 		current = next;
// 	}
// 	*env = NULL;
// }

// void	free_list_path(t_list_path **path)
// {
// 	t_list_path	*current;
// 	t_list_path	*next;

// 	current = *path;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->name_path);
// 		free(current);
// 		current = next;
// 	}
// 	*path = NULL;
// }