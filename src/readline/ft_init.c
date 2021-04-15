/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:58:59 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 14:59:01 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_size_init(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	g_env.col = w.ws_col;
	g_env.row = w.ws_row;
}

void	ft_init_c1(void)
{
	g_env.working_dir = ft_get_var_value(g_env.var, "PWD");
	g_env.working_dir = (!g_env.working_dir) ?
	ft_strdup("/") : ft_strdup(g_env.working_dir);
	g_env.old_working_dir = NULL;
	g_env.home = ft_get_var_value(g_env.var, "HOME");
	g_env.home = (!g_env.home) ? ft_strdup("/") : ft_strdup(g_env.home);
	g_env.res_stdin = dup(0);
	g_env.res_stdout = dup(1);
	g_env.res_stderr = dup(2);
	ft_size_init();
	ft_load_his();
	ft_load_alias();
}

void	ft_init(char **envp)
{
	g_env.gnl = NULL;
	g_env.var = ft_load_env(envp);
	g_env.his = NULL;
	g_env.al = NULL;
	g_env.auto_com = NULL;
	g_env.cur_col = 0;
	g_env.cur_row = 0;
	g_env.cur_all_col = 0;
	g_env.cur_all_row = 0;
	g_env.last_char_row = 0;
	g_env.last_char_col = 0;
	g_env.cur_mult_col = 0;
	g_env.select_mode = 0;
	g_env.select_line = NULL;
	g_env.running_proc = 0;
	g_env.inside_prompt = 0;
	g_env.inside_heredoc = 0;
	ft_init_c1();
}

void	ft_free_env_c1(void)
{
	void *tmp;

	while (g_env.his)
	{
		tmp = g_env.his->next;
		free(g_env.his->line);
		free(g_env.his->dis_line);
		free(g_env.his);
		g_env.his = tmp;
	}
	while (g_env.al)
	{
		tmp = g_env.al->next;
		free(g_env.al->alias);
		free(g_env.al->str);
		free(g_env.al);
		g_env.al = tmp;
	}
}

void	ft_free_env(void)
{
	free(g_env.working_dir);
	if (g_env.old_working_dir)
		free(g_env.old_working_dir);
	free(g_env.home);
	if (g_env.prompt)
		free(g_env.prompt);
	if (g_env.branch)
		free(g_env.branch);
	if (g_env.line)
		free(g_env.line);
	ft_free_var(&(g_env.var));
	while (g_env.his && g_env.his->prev)
		g_env.his = g_env.his->prev;
	ft_free_env_c1();
}
