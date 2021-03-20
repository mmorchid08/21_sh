/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exexc2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:51:30 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/20 14:52:31 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_execution.h"

void			exection(char *binary, char **argv, char **env)
{
	if (execve(binary, argv, env) < 1)
	{
		ft_putendl("error execute binary");
		exit(EXIT_FAILURE);
	}
}

void			ft_exece(t_tokens *begin)
{
	char		*bin_path;
	char		**argv;
	char		**arr_env;
	t_list_path	*path_list;

	bin_path = NULL;
	if (ft_strchr(begin->data, '/') ||
		(bin_path = open_paths(begin, &path_list)))
	{
		if (bin_path == NULL)
			bin_path = ft_strdup(begin->data);
		argv = ft_convert_list_array(begin->args);
		arr_env = ft_convert_list_env_array();
		exection(bin_path, argv, arr_env);
		ft_free_table(&arr_env);
		ft_free_table(&argv);
		free(bin_path);
	}
	else
	{
		ft_check_error(begin->data);
		exit(1);
	}
	if (bin_path != NULL)
		free_list_path(&path_list);
}
