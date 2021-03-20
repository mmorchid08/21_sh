/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:14:26 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/20 16:19:25 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execution.h"

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
		{
			line = tmp->data;
			tmp->data = ft_strmap2(tmp->data, &ft_decode_char);
		}
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
