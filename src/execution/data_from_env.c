/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:16:40 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/18 14:50:54 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

t_var	*get_malloc_key_value(char *key, char *value)
{
	t_var	*nev;

	nev = (t_var *)malloc(sizeof(t_var));
	nev->key = key;
	nev->value = value;
	nev->next = NULL;
	return (nev);
}
