/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:14:26 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/19 16:33:08 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

char	*ft_strjoin_one_charatcter(char const *s1, char const s2)
{
	int		i;
	char	*str;

	i = 0;
	if (s1 && s2)
	{
		str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1 + 1));
		if (!str)
			return (NULL);
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		str[i++] = s2;
		str[i] = '\0';
		return (str);
	}
	return (0);
}

void	ft_cut_buf(char *buf)
{
	buf[ft_strlen(buf) - 1] = '\0';
}

int		ft_isaggr(char *s1, char *s2, int n)
{
	int		offset;

	offset = 0;
	while (*s1 && *s1 != ' ')
	{
		if (ft_strncmp(s1, s2, n) == 0)
			return (offset);
		offset++;
		s1++;
	}
	return (0);
}

int		ft_get_type(char *c, int offset)
{
	int i;

	i = 0;
	while (i < offset)
	{
		if (ft_isdigit(c[i]))
			i++;
		else
			return (WORD);
	}
	return (PRE_AGGREGATION_NUMBER);
}

t_content	check_character_for_split(char *c)
{
	int	offset;

	if ((offset = ft_isaggr(c, ">>", 2)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, ">>", 2) == 0)
		return ((t_content){2, REDIRECTION_RIGHT_RIGHT});
	if ((offset = ft_isaggr(c, "<<<", 3)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, "<<<", 3) == 0)
		return ((t_content){3, REDIRECTION_LEFT_LEFT_LEFT});
	if ((offset = ft_isaggr(c, "<<", 2)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, "<<", 2) == 0)
		return ((t_content){2, REDIRECTION_LEFT_LEFT});
	if ((offset = ft_isaggr(c, ">&", 2)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, ">&", 2) == 0)
		return ((t_content){2, REDIRECTION_RIGHT_AGGREGATION});
	if ((offset = ft_isaggr(c, "<&", 2)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, "<&", 2) == 0)
		return ((t_content){2, REDIRECTION_LEFT_AGGREGATION});
	if ((offset = ft_isaggr(c, "<", 1)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, "<", 1) == 0)
		return ((t_content){1, REDIRECTION_LEFT});
	if ((offset = ft_isaggr(c, ">", 1)) != 0)
		return ((t_content){offset, ft_get_type(c, offset)});
	if (ft_strncmp(c, ">", 1) == 0)
		return ((t_content){1, REDIRECTION_RIGHT});
	if (ft_strncmp(c, "|", 1) == 0)
		return ((t_content){1, PIPE});
	if (ft_strncmp(c, ";", 1) == 0)
		return ((t_content){1, SEMICOLON});
	if ((ft_strncmp(c, " ", 1) == 0) || (ft_strncmp(c, "\t", 1) == 0))
		return ((t_content){1, SPACE});
	return ((t_content){0, 0});
}

t_tokens	*new_node(char *data, int type)
{
	t_tokens	*node;

	node = (t_tokens *)malloc(sizeof(t_tokens));
	node->data = ft_strdup(data);
	node->type = type;
	node->status = 0;
	node->here = NULL;
	node->args = NULL;
	node->next = NULL;
	return (node);
}

void	append_list_tokens(t_tokens **tokens, char *data, int type)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (tmp == NULL)
	{
		tmp = new_node(data, type);
		if (type == WORD)
			tmp->args = new_node(tmp->data, WORD_ARG);
		*tokens = tmp;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (type == WORD && tmp->type == WORD)
			append_list_tokens(&(tmp->args), data, WORD_ARG);
		else
		{
			tmp->next = new_node(data, type);
			if (type == WORD)
				tmp->next->args = new_node(tmp->next->data, WORD_ARG);
		}
	}
}

int		check_red(int type)
{
	if (type == 1 || type == 2 || type == 3 || type == 4
			|| type == 5 || type == 6 || type == 7)
		return (1);
	return (0);
}

t_tokens	*handling(char *line)
{
	t_vari		var;
	t_tokens	*tokens;
	t_tokens	*tmp;
	t_content	content;

	var.i = 0;
	tokens = NULL;
	var.pt = NULL;
	var.toto = NULL;
	while (line[var.i])
	{
		var.token = ft_strdup("");
		content = check_character_for_split(&line[var.i]);
		if (content.index)
		{
			if (line[var.i] != ' ' && line[var.i] != '\t')
			{
				var.toto = ft_strsub(line, var.i, content.index);
				var.pt = var.token;
				var.token = ft_strjoin(var.token, var.toto);
				ft_strdel(&var.pt);
				ft_strdel(&var.toto);
				append_list_tokens(&tokens, var.token, content.type);
				ft_bzero(var.token, ft_strlen(var.token));
			}
			ft_strdel(&var.token);
			var.i = var.i + content.index;
		}
		else
		{
			if (!(ft_isprint(line[var.i])
			|| (line[var.i] < 0 && line[var.i] >= -5)
			|| line[var.i] == '\n'))
				var.i++;
			while ((ft_isprint(line[var.i])
			|| (line[var.i] < 0 && line[var.i] >= -5)
			|| line[var.i] == '\n') && content.index == 0)
			{
				var.pt = var.token;
				var.token = ft_strjoin_one_charatcter(var.token, line[var.i]);
				ft_strdel(&var.pt);
				var.i++;
				content = check_character_for_split(&line[var.i]);
				if (content.index != 0)
				{
					content.type = 0;
					break ;
				}
			}
			append_list_tokens(&tokens, var.token, content.type);
			ft_bzero(var.token, ft_strlen(var.token));
			ft_strdel(&var.token);
		}
	}
	tmp = tokens;
	while (tmp)
	{
		if (check_red(tmp->type) && tmp->next != NULL && tmp->next->type == 0)
			tmp->next->type = REDIRECTION_WORD;
		if (tmp->type == 0)
			tmp->data = ft_strmap(tmp->data, &ft_decode_char);
		tmp = tmp->next;
	}
	return (tokens);
}

void	main_c1(void)
{
	char		*line;
	char		*tmp;
	t_tokens	*tokens;

	tmp = ft_readline();
	ft_save_fds();
	line = (tmp) ? ft_strtrim(tmp) : NULL;
	if (g_env.inside_prompt != -1 && !g_env.auto_step && tmp && *line)
	{
		ft_parse(&line);
		tokens = handling(line);
		if (!ft_checksemi(tokens) && !err_pars(tokens) && !ft_check_fd(tokens))
			handling_semi(tokens);
		free_list_token(&tokens);
	}
	(line) ? free(line) : 1;
	(tmp) ? free(tmp) : 1;
	if (g_env.auto_step <= 1)
	{
		if (g_env.auto_com)
			ft_strdel(&g_env.auto_com);
		g_env.auto_step = 0;
		g_env.auto_select = -1;
		g_env.auto_len = -1;
	}
}

int		main(int argc, char **argv, char **envp)
{
	argc = argc;
	argv = argv;
	ft_set_input_mode();
	if (tgetent(NULL, (getenv("TERM")) ? getenv("TERM") : TERM) > 0)
	{
		ft_signal_handle();
		ft_init(envp);
		while (1)
		{
			ft_get_prompt();
			ft_putstr(g_env.prompt);
			g_env.prompt_len = g_env.multi_prompt_len;
			g_env.cur_col = 0;
			g_env.cur_row = 0;
			g_env.inside_prompt = 0;
			g_env.cur_all_col = 0;
			g_env.cur_all_row = 0;
			main_c1();
		}
		ft_free_env();
	}
	return (0);
}
