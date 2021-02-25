/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:00:31 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 15:00:32 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*ft_get_username(void)
{
	uid_t			uid;
	struct passwd	*pw;

	uid = geteuid();
	pw = getpwuid(uid);
	if (pw)
		return (ft_strdup(pw->pw_name));
	return (ft_strdup("NO_USERNAME"));
}

char	*ft_get_hostname(void)
{
	char	hostbuffer[256];
	char	*tmp;

	ft_bzero(hostbuffer, 256);
	if (gethostname(hostbuffer, sizeof(hostbuffer)) != -1)
	{
		if (!(tmp = ft_strchr(hostbuffer, '.')))
			return (ft_strdup(hostbuffer));
		*tmp = '\0';
		return (ft_strdup(hostbuffer));
	}
	return (ft_strdup("NO_HOSTNAME"));
}

char	*ft_get_wd(void)
{
	char	*res;
	int		len;

	len = ft_strlen(g_env.home);
	if (g_env.working_dir && g_env.home
	&& ft_strnequ(g_env.home, g_env.working_dir, len))
		res = ft_free_strjoin(ft_strdup("~"),
		ft_strdup(g_env.working_dir + len));
	else
		res = ft_strdup(g_env.working_dir);
	return (res);
}

void	ft_get_prompt(void)
{
	char	*line;
	char	*pwd;

	line = ft_strdup("╭─"C_RED);
	g_env.username = ft_get_username();
	g_env.hostname = ft_get_hostname();
	pwd = ft_get_wd();
	ft_get_git_branch(g_env.working_dir);
	line = ft_free_strjoin(line, g_env.username);
	line = ft_free_strjoin(line, ft_strdup(C_RESET":"C_RED));
	line = ft_free_strjoin(line, g_env.hostname);
	line = ft_free_strjoin(line, ft_strdup(C_RESET" "C_GRN));
	line = ft_free_strjoin(line, ft_free_strjoin(pwd,
	(g_env.branch) ? ft_strdup(g_env.branch) : ft_strdup("")));
	line = ft_free_strjoin(line, ft_strdup(C_RESET"\n"));
	line = ft_free_strjoin(line, ft_strdup((!getuid()) ?
	C_RESET"╰─# " : C_RESET"╰─$ "));
	if (g_env.prompt)
		ft_strdel(&(g_env.prompt));
	g_env.prompt = line;
	g_env.prompt_len = 4;
	g_env.multi_prompt_len = ((int)g_env.prompt_len > g_env.col) ?
	g_env.prompt_len % g_env.col : g_env.prompt_len;
}
