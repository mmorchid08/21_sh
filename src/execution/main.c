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

void	ft_cut_buf(char *buf) // 2 >&-  | 2>&-
{
	buf[ft_strlen(buf) - 1] = '\0';
}

int ft_isaggr(char *s1, char *s2, int n) 
{
    int offset = 0;
    
    while (*s1 && *s1 != ' ') 
    {
        if (ft_strncmp(s1, s2, n) == 0)
            return offset;
        offset++;
        s1++;
    }
    return 0;
}

t_content check_character_for_split(char *c)
{
    int offset;

    if ((offset = ft_isaggr(c, ">>", 2)) != 0)
        return((t_content){offset, PRE_AGGREGATION_NUMBER});
    if(ft_strncmp(c, ">>", 2) == 0)
        return((t_content){2,REDIRECTION_RIGHT_RIGHT});
    
    // if(ft_strncmp(c, "<<<", 3) == 0)
    //     return((t_content){3,REDIRECTION_LEFT_LEFT_LEFT});
    if ((offset = ft_isaggr(c, "<<", 2)) != 0)
        return((t_content){offset, PRE_AGGREGATION_NUMBER});
    if(ft_strncmp(c, "<<", 2) == 0)
        return((t_content){2,REDIRECTION_LEFT_LEFT});
    //----------------------------
    if ((offset = ft_isaggr(c, ">&", 2)) != 0)
        return((t_content){offset, PRE_AGGREGATION_NUMBER});
    if(ft_strncmp(c, ">&", 2) == 0)
        return((t_content){2,REDIRECTION_RIGHT_AGGREGATION});
    //-------------------------
    if ((offset = ft_isaggr(c, "<&", 2)) != 0)
        return((t_content){offset, PRE_AGGREGATION_NUMBER});
    if(ft_strncmp(c, "<&", 2) == 0)
        return((t_content){2,REDIRECTION_LEFT_AGGREGATION});
    //----------------------------
    if ((offset = ft_isaggr(c, "<", 1)) != 0)
        return((t_content){offset, PRE_AGGREGATION_NUMBER});
    if(ft_strncmp(c, "<", 1) == 0)
        return((t_content){1,REDIRECTION_LEFT});
    //----------------------------
    if ((offset = ft_isaggr(c, ">", 1)) != 0)
        return((t_content){offset, PRE_AGGREGATION_NUMBER});
    if(ft_strncmp(c, ">", 1) == 0)
        return((t_content){1,REDIRECTION_RIGHT});
    //-----------------------------------
    if(ft_strncmp(c, "&&", 2) == 0)
        return((t_content){2,AND});
    if(ft_strncmp(c, "||", 2) == 0)
        return((t_content){2,OR});
    if(ft_strncmp(c, "|", 1) == 0)
        return((t_content){1,PIPE});  
    if(ft_strncmp(c, ";", 1) == 0)
        return((t_content){1,SEMICOLON});  
    if(ft_strncmp(c, "&", 1) == 0)
        return((t_content){1,AMP});
    if((ft_strncmp(c, " ", 1) == 0) || (ft_strncmp(c, "\t", 1) == 0))
        return((t_content){1,SPACE});
    return((t_content){0,0});
}

t_tokens *new_node(char *data, int type)
{
    t_tokens *node;
    
    node = (t_tokens *)malloc(sizeof(t_tokens));
    node->data = ft_strdup(data);
    node->type = type;
    node->here = NULL;
    node->next = NULL;
    return(node);
}

void append_list_tokens(t_tokens **tokens, char *data, int type)
{
    t_tokens *tmp;

    tmp = *tokens;
    if (tmp == NULL)
    {
        tmp = new_node(data,type);
        *tokens = tmp;  
    }
    else
    {
        while (tmp->next != NULL)
            tmp = tmp->next;        
        tmp->next = new_node(data,type);
    }

}
int check_red(int type)
{
    if (type == 1 || type == 2 ||type == 3||type == 4||type == 5||type == 6||type == 7) 
        return(1);
    return(0);
}

t_tokens *handling(char *line)
{
    int i;
    char *token;
    char *pt;
    t_tokens *tokens;
    t_tokens *tmp;
    t_tokens *tmp2;
    char *toto = NULL;
    t_content content;

    i = 0;
    tokens = NULL;
    pt = NULL;
    while (line[i])
    {
        token = ft_strdup("");
        content = check_character_for_split( &line[i]);
        if(content.index)
        {
            if(line[i] != ' ' && line[i] != '\t')
            {
                toto = ft_strsub(line, i , content.index);
                pt = token;
                token = ft_strjoin(token,toto);
                ft_strdel(&pt);
                ft_strdel(&toto);
                append_list_tokens(&tokens, token,content.type);
                ft_bzero(token,ft_strlen(token));
            }
            ft_strdel(&token);
            i = i + content.index;
        }
        else if(content.index == 0)
        {
            if (!(ft_isprint(line[i]) || (line[i] < 0 && line[i] >= -5) || line[i] == '\n'))
                i++;
            while((ft_isprint(line[i]) || (line[i] < 0 && line[i] >= -5) || line[i] == '\n') && content.index == 0) 
            {
                pt = token;
                token = ft_strjoin_one_charatcter(token,line[i]);
                ft_strdel(&pt);
                i++;
                content = check_character_for_split(&line[i]);
                if (content.index != 0)
                {
                    content.type =0;              
                    break;
                }
            }
            append_list_tokens(&tokens, token, content.type);
            ft_bzero(token,ft_strlen(token));
            ft_strdel(&token);
        }
        else 
        {
            i++;
            ft_strdel(&token);
        }
    }
    tmp = tokens;
    tmp2 = tokens;
    while (tmp)
    {
        if (check_red(tmp->type) == 1 &&  tmp->next != NULL && tmp->next->type == 0)
            tmp->next->type = REDIRECTION_WORD;
        if (tmp->type == 0)
            tmp->data = ft_strmap(tmp->data, &ft_decode_char);
        tmp = tmp->next;
    }
    while (tmp2)
    {
        if (tmp2->next != NULL && tmp2->next->type == 5) // 2>&
        {
            if (ft_strcmp(tmp2->data, "0") == 0 ||ft_strcmp(tmp2->data, "1") == 0 || 
            ft_strcmp(tmp2->data, "2") == 0)
               tmp2->type = WORD_REDIRECTION;
        }
        tmp2 = tmp2->next;
    }
    return(tokens);
}

void	main_c1()
{
	char	*line;
	char	*tmp;

    t_tokens *tokens;
    t_tokens *tmp1;
    t_tokens *tmp2;
    t_tokens *tmp3;

	tmp = ft_readline();
	line = (tmp) ? ft_strtrim(tmp) : NULL;
	if (g_env.inside_prompt != -1 && !g_env.auto_step && tmp && *line)
	{
        ft_parse(&line);
		tokens = handling(line);
        tmp1 = tokens;
        tmp2 = tokens;
        tmp3 = tokens;
        if (!ft_check_multi_semi(tmp1) && !ft_error_parse(tmp2) && !ft_check_bad_fd(tmp3))
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