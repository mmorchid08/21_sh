/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exexc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:29:55 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/25 17:35:53 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"


t_list_path	*get_malloc_value_path(char *value)
{
	t_list_path *nev;

	nev = (t_list_path *)malloc(sizeof(t_list_path));
	nev->name_path = value;
	nev->next = NULL;
	return (nev);
}

char	*ft_read_from_dir(t_list_path *tmp2, t_tokens *token_begin)
{
	DIR				*dir;
	struct dirent	*sd;
	char			*token[2];

	if ((dir = opendir(tmp2->name_path)) != NULL)
	{
		while ((sd = readdir(dir)) != NULL)
			if (ft_strcmp(token_begin->data, sd->d_name) == 0)
			{
				token[1] = ft_strjoin(tmp2->name_path, "/");
				token[0] = ft_strjoin(token[1], sd->d_name);
				free(token[1]);
				closedir(dir);
				return (token[0]);
			}
		closedir(dir);
	}
	return (NULL);
}

void		ft_path_list(char *path_str,t_list_path **path_list)
{
	t_list_path	*tmp;
	int			i;
    char **tab_path;

	i = 0;
	tmp = NULL;
    tab_path = NULL;
	*path_list = NULL;
	tab_path = ft_strsplit(path_str, ':');
	while (tab_path[i])
	{
		if (tmp == NULL)
		{
			tmp = get_malloc_value_path(tab_path[i]);
			*path_list = tmp;
		}
		else
		{
			tmp->next = get_malloc_value_path(tab_path[i]);
			tmp = tmp->next;
		}
		i++;
	}    
	free(tab_path);
}

char	*open_paths(t_tokens *begin, t_list_path **path_list)
{
	t_var	*tmp;
	t_list_path	*tmp2;
	// t_list_path	*path_list;
	char		*path;

	tmp = g_env.var;
	path = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
		{
			ft_path_list(tmp->value, path_list); 
			tmp2 = *path_list;
			while (tmp2 != NULL)
			{
				path = ft_read_from_dir(tmp2, begin);
				if (path != NULL)
					return (path);
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	exection(char *binary, char **argv, char **env)
{
	if (execve(binary, argv, env) < 1)
	{
		ft_putendl("error execute binary");
		exit(EXIT_FAILURE);
	}
}

void ft_exece(t_tokens *begin)
{
    char		*bin_path;
	char		**argv;
	char		**arr_env;
	t_list_path	*path_list;

	
	ft_unset_input_mode();
    if (ft_strchr(begin->data, '/') || (bin_path = open_paths(begin,&path_list)))
	{
		if (bin_path == NULL)
			bin_path = ft_strdup(begin->data);
		argv = ft_convert_list_array(begin);
		arr_env = ft_convert_var_array();
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