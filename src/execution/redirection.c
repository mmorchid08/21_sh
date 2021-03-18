/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:52:46 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/18 12:02:48 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

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

int		ft_count(t_tokens *begin, t_tokens *finish)
{
	int	count;

	count = 0;
	while (begin != finish)
	{
		if (begin->type == 0)
			count++;
		begin = begin->next;
	}
	return (count);
}

int		authorization_re(t_tokens *token)
{
	int		i_data;
	char	*s_data;

	s_data = NULL;
	i_data = ft_atoi(token->data);
	s_data = ft_itoa(i_data);
	if (ft_strcmp(token->data, s_data) == 0)
	{
		if (i_data >= 0 && i_data <= 2)
		{
			if (ft_strcmp(token->data, "0") == 0)
				return (1);
			else if (ft_strcmp(token->data, "1") == 0)
				return (1);
			else if (ft_strcmp(token->data, "2") == 0)
				return (1);
		}
	}
	return (0);
}

void	redirection_right_agg(char *prev_data, char *file_name, int fd)
{
	if (ft_strcmp(file_name, "-") == 0)
	{
		if (ft_strcmp(prev_data, "0") == 0)
			close(READ_END);
		else if (ft_strcmp(prev_data, "1") == 0)
			close(WRITE_END);
		else if (ft_strcmp(prev_data, "2") == 0)
			close(ERROR_END);
	}
	else if (ft_get_type(file_name, ft_strlen(file_name)) == WORD)
		redirection_out(file_name, fd);
	else
		dup2(ft_atoi(file_name), fd);
}

int		ft_check_is_num(char *data)
{
	int	num;
	int	i;

	i = 0;
	num = ft_atoi(data);
	if (num != 0)
		return (1);
	return (0);
}

void	redirection_out(char *file_name, int fd)
{
	int out;

	out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	dup2(out, fd);
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

void	redirection(t_tokens *begin)
{
	t_tokens	*prev;
	int			def_fd;

	prev = NULL;
	while (begin)
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
		else if (begin->type == REDIRECTION_RIGHT_AGGREGATION)
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
