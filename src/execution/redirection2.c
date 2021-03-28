/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:38:18 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/21 12:54:39 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

void	redirection_out(char *file_name, int fd, int fd2)
{
	int out;

	out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	dup2(out, fd);
	if (fd2 >= 0)
		dup2(out, fd2);
	close(out);
}

void	redirection_in(char *file_name, int fd)
{
	int in;

	in = open(file_name, O_RDONLY);
	dup2(in, fd);
	close(in);
}

void	redirection_out_out(char *file_name, int fd)
{
	int out_out;

	out_out = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0600);
	dup2(out_out, fd);
	close(out_out);
}

void	redirection_right_agg(t_tokens *token)
{
	if (token->sub_fd < 0 && !token->filename)
	{
		dup2(token->sub_fd, token->pre_fd);
	}
	else
		redirection_out(token->filename, token->pre_fd, 2);
	if (token->close)
		close(token->pre_fd);
}

void	ft_herestr(char *line)
{
	pid_t	current_pid;
	int		fd[2];

	pipe(fd);
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
		ft_putendl_fd(line, STDOUT_FILENO);
		exit(0);
	}
}
