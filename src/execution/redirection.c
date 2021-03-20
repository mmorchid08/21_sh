/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:52:46 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/20 17:34:39 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	ft_heredoc_sequel(char *line, int current_pid, int fd[2], char *str)
{
	current_pid = fork();
	if (current_pid > 0)
	{
		waitpid(current_pid, 0, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
	}
	else if (current_pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ft_putendl_fd(str, STDOUT_FILENO);
		exit(0);
	}
}

void	ft_heredoc(char *line)
{
	char	*str;
	char	*tmp;
	pid_t	current_pid;
	int		fd[2];

	pipe(fd);
	g_env.prompt_len = ft_strlen("heredoc> ");
	str = NULL;
	while (1)
	{
		ft_putstr("heredoc> ");
		tmp = ft_readline();
		if (ft_strequ(tmp, line))
			break ;
		if (tmp)
		{
			str = (str) ? ft_free_strjoin(str, ft_strdup("\n")) : ft_strnew(0);
			str = ft_free_strjoin(str, tmp);
		}
	}
	ft_heredoc_sequel(line, current_pid, fd, str);
}

void	redirection2(t_tokens *begin, int def_fd, t_tokens *prev)
{
	if (begin->type == REDIRECTION_RIGHT)
	{
		def_fd = 1;
		if (prev->type == 17)
			def_fd = atoi(prev->data);
		redirection_out(begin->next->data, def_fd);
	}
	else if (begin->type == REDIRECTION_LEFT)
	{
		def_fd = 0;
		if (prev->type == 17)
			def_fd = atoi(prev->data);
		redirection_in(begin->next->data, def_fd);
	}
	else if (begin->type == REDIRECTION_RIGHT_RIGHT)
	{
		def_fd = 1;
		if (prev->type == 17)
			def_fd = atoi(prev->data);
		redirection_out_out(begin->next->data, def_fd);
	}
	else if (begin->type == REDIRECTION_LEFT_LEFT)
		ft_heredoc(begin->next->data);
	else if (begin->type == REDIRECTION_LEFT_LEFT_LEFT)
		ft_herestr(begin->next->data);
}

void	redirection(t_tokens *begin)
{
	t_tokens	*prev;
	int			def_fd;

	prev = NULL;
	while (begin)
	{
		redirection2(begin, def_fd, prev);
		if (begin->type == REDIRECTION_RIGHT_AGGREGATION)
		{
			def_fd = 1;
			if (prev->type == 17)
				def_fd = atoi(prev->data);
			redirection_right_agg(prev->data, begin->next->data, def_fd);
		}
		else if (begin->type == REDIRECTION_LEFT_AGGREGATION)
		{
			def_fd = 0;
			if (prev->type == 17)
				def_fd = atoi(prev->data);
			dup(def_fd);
		}
		prev = begin;
		begin = begin->next;
	}
}
