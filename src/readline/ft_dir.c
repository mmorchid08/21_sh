/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:58:22 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:58:23 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_di	*ft_new_dir(char *name)
{
	t_di *di;

	if (!(di = (t_di *)malloc(sizeof(t_di))))
		exit(1);
	di->name = name;
	di->next = NULL;
	return (di);
}

void	ft_add_dir(t_di **head, t_di *new)
{
	t_di *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	ft_add_dir(&(tmp->next), new);
}

void	ft_free_dir(t_di **head)
{
	t_di	*di;
	t_di	*tmp;

	di = *head;
	while (di)
	{
		free(di->name);
		tmp = di->next;
		free(di);
		di = tmp;
	}
}

t_di	*ft_load_dir(char *var)
{
	t_di			*di;
	DIR				*path;
	struct dirent	*file;
	struct stat		st;
	char			*tmp;

	di = NULL;
	if ((path = opendir(var)))
	{
		while ((file = readdir(path)) != NULL)
		{
			tmp = ft_strjoin(var, "/");
			tmp = ft_free_strjoin(tmp, ft_strdup(file->d_name));
			if (stat(tmp, &st) == 0 && S_ISREG(st.st_mode))
				ft_add_dir(&di, ft_new_dir(ft_strdup(file->d_name)));
			free(tmp);
		}
		closedir(path);
	}
	return (di);
}
