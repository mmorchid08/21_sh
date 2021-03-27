/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:52:46 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/21 12:54:29 by mmorchid         ###   ########.fr       */
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

void	redirection2(t_tokens *begin)
{
	if (begin->type == REDIRECTION_RIGHT)
	{
		(begin->pre_fd < 0) && (begin->pre_fd = 1);
		redirection_out(begin->filename, begin->pre_fd, -1);
	}
	else if (begin->type == REDIRECTION_LEFT)
	{
		(begin->pre_fd < 0) && (begin->pre_fd = 0);
		redirection_in(begin->filename, begin->pre_fd);
	}
	else if (begin->type == REDIRECTION_RIGHT_RIGHT)
	{
		(begin->pre_fd < 0) && (begin->pre_fd = 1);
		redirection_out_out(begin->filename, begin->pre_fd);
	}
	else if (begin->type == REDIRECTION_LEFT_LEFT)
		ft_heredoc(begin->filename);
	else if (begin->type == REDIRECTION_LEFT_LEFT_LEFT)
		ft_herestr(begin->filename);
}

void	redirection(t_tokens *begin)
{
	while (begin && check_red(begin->type))
	{
		redirection2(begin);
		if (begin->type == REDIRECTION_RIGHT_AGGREGATION)
		{
			(begin->pre_fd < 0) && (begin->pre_fd = 1);
			redirection_right_agg(begin);
		}
		else if (begin->type == REDIRECTION_LEFT_AGGREGATION)
		{
			(begin->pre_fd < 0) && (begin->pre_fd = 0);
			redirection_right_agg(begin);
		}
		begin = begin->next;
	}
}
