/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:30:30 by mmorchid          #+#    #+#             */
/*   Updated: 2021/02/23 16:10:05 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_execution.h"

char	*ft_strjoin_one_charatcter(char const *s1, char const s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
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

t_content chek_character_for_split(char *c)
{
    if(ft_strncmp(c, ">>", 2) == 0)
        return((t_content){2,REDIRECTION_RIGHT_RIGHT});
    if(ft_strncmp(c, "<<", 2) == 0)
        return((t_content){2,REDIRECTION_LEFT_LEFT});
    if(ft_strncmp(c, ">&", 2) == 0)
        return((t_content){2,REDIRECTION_RIGHT_AGGREGATION});
    if(ft_strncmp(c, "<&", 2) == 0)
        return((t_content){2,REDIRECTION_LEFT_AGGREGATION});
    if(ft_strncmp(c, "<", 1) == 0)
        return((t_content){1,REDIRECTION_LEFT});
    if(ft_strncmp(c, ">", 1) == 0)
        return((t_content){1,REDIRECTION_RIGHT});
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
        return((t_content){1,0});
    return((t_content){0,0});
}

t_tokens *new_node(char *data, int type)
{
    t_tokens *node;
    
    node = (t_tokens *)malloc(sizeof(t_tokens));
    node->data = ft_strdup(data);
    node->type = type;
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
    if (type == 1 || type == 2 ||type == 3 
        ||type == 4 ||type == 5 
        || type == 6 ||type == 7) 
        return (1);
    return (0);
}
t_tokens *handling(char *line)
{
    int i;
    char *token;
    char *pt;
    t_tokens *tokens;
    t_tokens *tmp;
    char *toto = NULL;
    t_content content;
    int m;

    i = 0;
    tokens = NULL;
    while (line[i])
    {
        token = ft_strdup("");
        content = chek_character_for_split(&line[i]);
        if(content.index == 2)
        {
            if(line[i] != ' ' && line[i] != '\t')
            {
                toto = ft_strsub(line, i , 2);
                token = ft_strjoin(token,toto);
                append_list_tokens(&tokens, token,content.type);
                ft_bzero(token,ft_strlen(token));
            }
            i = i + 2;
        }
        else if(content.index == 1)
        {
            if(line[i] != ' ' && line[i] != '\t')
            {
                token = ft_strjoin_one_charatcter(token,line[i]);
                append_list_tokens(&tokens, token,content.type);
                ft_bzero(token,ft_strlen(token));
            }
            i++;
        }
        else if(content.index == 0)
        {
            while(ft_isprint(line[i]) && content.index == 0) 
            {
                token = ft_strjoin_one_charatcter(token,line[i]);
                i++;
                content = chek_character_for_split(&line[i]);
                if (content.index != 0)
                {
                    content.type =0;              
                    break;
                }
            }
            append_list_tokens(&tokens, token,content.type);
         }
    }
    tmp = tokens;
    while (tmp)
    {
        if (check_red(tmp->type) == 1 &&  tmp->next != NULL &&tmp->next->type == 0)
            tmp->next->type = REDIRECTION_WORD;
        tmp = tmp->next;
    }
    return(tokens);
}

int main(int argc, char **argv, char **env)
{
    argc = 0;
    argv = NULL;
    char buffer[1024];
    t_tokens *tokens;
    t_tokens *tmp;
    t_tokens *tmp2;
    t_tokens *tmp3;
    t_pipe *pipe;
    t_semi *semi;
    t_list_env *list_env;
    int r;
    int count = 0;

    ft_env_list(env, &list_env);
    while(1)
    {
        ft_putstr("$>");
        ft_bzero(buffer,1024);
        r = read(0, buffer,1024);
        ft_cut_buf(buffer);
        if (ft_chek_espace(buffer) == 0)
			continue ;
        tokens = handling(ft_strdup(buffer));
        tmp = tokens;
        tmp2 = tokens;
        tmp3 = tokens;
        if(ft_check_multi_semi(tmp) == 1)
            continue ;
        if(ft_error_parse(tmp2) == 1)
            continue ;
        if (ft_check_bad_fd(tmp) == 1)
            continue ;
        handling_semi(tokens, env,list_env);
    }
    return(0);
}
