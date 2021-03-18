/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:00:13 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/18 15:09:04 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_encode_char(char *pos, int type)
{
	if (*pos == ' ')
		*pos = -1;
	else if (type == 39 && (*pos == '$'))
		*pos = -2;
	else if (*pos == '|')
		*pos = -3;
	else if (*pos == ';')
		*pos = -4;
	else if (*pos == '&')
		*pos = -5;
}

char	ft_decode_char(char c)
{
	if (c == -1)
		c = ' ';
	else if (c == -2)
		c = '$';
	else if (c == -3)
		c = '|';
	else if (c == -4)
		c = ';';
	else if (c == -5)
		c = '&';
	return (c);
}

void	ft_manage_newline_c1(char **copy, int *flag, char **str)
{
	ft_putstr("newline> ");
	*str = ft_readline();
	*copy = ft_free_strjoin(*copy,
	ft_free_strjoin(ft_strdup("\n"), ft_strdup(*str)));
	*flag = 1;
}

void	ft_manage_newline(char **line, char **copy)
{
	char	*str;
	int		len;
	int		flag;

	len = ft_strlen(*line) - 1;
	if (len >= 0 && (*line)[len] == 92)
	{
		(*line)[len] = '\0';
		g_env.inside_prompt = 1;
		while (g_env.inside_prompt == 1)
		{
			ft_manage_newline_c1(copy, &flag, &str);
			len = ft_strlen(str) - 1;
			if (len >= 0 && str[len] == 92)
			{
				str[len] = '\0';
				flag = 0;
			}
			(*line) = ft_free_strjoin((*line),
			ft_free_strjoin(ft_strdup("\n"), str));
			if (flag)
				break ;
		}
		(g_env.inside_prompt == 1) && (g_env.inside_prompt = 0);
	}
}

void	ft_check_users(char **val, char *user, int *i)
{
	DIR				*path;
	struct dirent	*file;
	struct stat		st;
	int				j;

	user = ft_strdup(user);
	if (stat("/Users", &st) != -1 &&
	S_ISDIR(st.st_mode) && (path = opendir("/Users")))
	{
		j = 0;
		while (user[j] && user[j] != ' ' && user[j] != '/')
			j++;
		(user + j != user) && (*(user + j) = '\0');
		while ((file = readdir(path)) != NULL)
			if (ft_strequ(user, file->d_name))
			{
				*val = ft_free_strjoin(ft_strdup("/Users/"), user);
				*i += ft_strlen(user);
				closedir(path);
				return ;
			}
		closedir(path);
	}
	free(user);
	*val = NULL;
}
