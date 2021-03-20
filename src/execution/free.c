/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:33:00 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/18 12:53:29 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	free_list_token(t_tokens **token)
{
	t_tokens	*current;
	t_tokens	*next;

	current = *token;
	while (current)
	{
		next = current->next;
		free(current->data);
		free_list_token(&(current->args));
		free(current);
		current = next;
	}
	*token = NULL;
}

void	free_list_path(t_list_path **path)
{
	t_list_path	*current;
	t_list_path	*next;

	current = *path;
	while (current != NULL)
	{
		next = current->next;
		free(current->name_path);
		free(current);
		current = next;
	}
	*path = NULL;
}
