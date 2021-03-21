/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 13:11:20 by mmorchid          #+#    #+#             */
/*   Updated: 2021/03/21 12:58:57 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTION_H
# define FT_EXECUTION_H

# include "ft_readline.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define REDIRECTION_RIGHT	1
# define REDIRECTION_LEFT	2
# define REDIRECTION_LEFT_LEFT	3
# define REDIRECTION_LEFT_LEFT_LEFT	7
# define REDIRECTION_RIGHT_RIGHT	4
# define REDIRECTION_RIGHT_AGGREGATION 5
# define ESPACE_REDIRECTION_RIGHT_AGGREGATION 55
# define REDIRECTION_LEFT_AGGREGATION	6
# define PRE_AGGREGATION_NUMBER  17
# define AND 8
# define OR 9
# define PIPE 10
# define SEMICOLON 11
# define AMP 12
# define REDIRECTION_WORD 13
# define WORD_REDIRECTION 14
# define WORD_REDIRECTION_ESPACE 16
# define WORD_ARG 17
# define WORD 0
# define READ_END 0
# define WRITE_END 1
# define ERROR_END 2
# define NUMBER_OF_STRING 7
# define MAX_STRING_SIZE 15
# define SPACE 15

typedef struct	s_tokens
{
	char			*data;
	int				type;
	char			*here;
	int				space_b;
	int				status;
	int				ret;
	struct s_tokens	*args;
	struct s_tokens	*next;
}				t_tokens;

typedef struct	s_vari
{
	int		i;
	char	*token;
	char	*pt;
	char	*toto;
}				t_vari;

typedef struct	s_list_path
{
	char				*name_path;
	struct s_list_path	*next;
}				t_list_path;

typedef struct	s_data_env
{
	char	*key;
	char	*value;
}				t_data_env;

typedef struct	s_content
{
	int	index;
	int type;
}				t_content;

typedef struct	s_pipe
{
	char			*data;
	int				type;
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_semi
{
	t_tokens		*begin;
	t_tokens		*finish;
	struct s_semi	*next;
}				t_semi;

typedef struct	s_fd
{
	int fd_old[2];
	int fd_new[2];
}				t_fd;

t_tokens		*handling(char *line);
void			handling_semi(t_tokens *tokens);
void			handling_pipe(t_tokens *start, t_tokens *list);
void			handling_command(t_tokens *begin, t_tokens *finish,
				t_fd fd, int pos, int count_pipe);
t_semi			*new_node_semi(char *data, int type);
t_tokens		*new_node(char *data, int type);
int				ft_check_builtins(char *table);
void			ft_verify_builtins(t_tokens *token_begin);
void			ft_operation_echo(t_tokens *token_begin);
void			redirection_out(char *file_name, int fd, int fd2);
void			redirection_out_out(char *file_name, int fd);
void			redirection_in(char *file_name, int fd);
char			**prepere_argv(t_tokens *begin, t_tokens *finish);
void			redirection(t_tokens *begin);
int				ft_chek_espace(char *buf);
void			ft_env_list(char **env);
void			ft_env_function(void);
void			free_list_env(void);
void			ft_add_to_env(t_data_env data_env);
void			ft_cat_new_env_to_key_value(t_data_env *data_env, char *buf);
void			ft_add_change_env(t_tokens *token_begin);
t_var			*get_malloc_key_value(char *key, char *value);
void			ft_delete_one_env(t_tokens *token_begin);
void			ft_operation_cd(t_tokens *token_begin);
char			*ft_get_home(void);
char			*ft_get_pwd();
char			*ft_get_old_pwd();
void			ft_tack_pwd();
void			ft_the_current(char *path);
void			ft_tilda(char *value, int len);
void			ft_write_path(char *value);
void			ft_work_hyphen(char *token);
void			exection(char *binary, char **argv, char **env);
t_list_path		*get_malloc_value_path(char *value);
char			*ft_read_from_dir(t_list_path *tmp2, t_tokens *token_begin);
void			ft_path_list(char *path_str, t_list_path **path_list);
char			*open_paths(t_tokens *begin, t_list_path **path_list);
void			ft_exece(t_tokens *begin);
char			**ft_convert_list_env_array(void);
char			**ft_convert_list_array(t_tokens *token_begin);
int				ft_count_env();
int				ft_count_tokens(t_tokens *token_begin);
void			free_list_token(t_tokens **token);
void			free_list_path(t_list_path **path);
void			ft_check_error(char *name);
int				ft_check_fd_sequel(int count, int data, t_tokens *tmp);
int				ft_checksemi(t_tokens *tmp);
int				ft_check_multi_pipe(t_tokens *tmp);
int				ft_check_fd(t_tokens *tmp);
int				err_pars(t_tokens *tmp);
int				ft_know_type(int type);
void			ft_save_fds(void);
void			ft_restore_fds(void);
t_var			*get_malloc_key_value(char *key, char *value);
void			ft_heredoc(char *line);
void			ft_herestr(char *line);
int				ft_get_type(char *c, int offset);
int				check_red(int type);
void			ft_operation_non_fork_cd(t_tokens *token_begin);
void			ft_verify_non_fork_builtins(t_tokens *token_begin);
int				ft_count_pipe(t_tokens *node);
int				ft_read_red_err(char *path, int type);
void			ft_exec(t_tokens *line);
void			ft_close_pipe(int pipecount);
int				ft_isaggr(char *s1, char *s2, int n);
void			redirection_right_agg(char *prev_data, char *file_name, int fd);
char			*ft_strjoin_one_charatcter(char const *s1, char const s2);
t_content		check_character_for_split(char *c);
void			append_list_tokens(t_tokens **tokens, char *data, int type);
void			ft_operation_non_fork_unalias(t_tokens *line);
void			ft_operation_non_fork_alias(t_tokens *line);
void			ft_list_alias(t_alias *al);
void			handling2(char *line, t_vari *var, t_content *content, t_tokens **tokens);
void			handling3(t_tokens	*tokens);
t_content		check_character_for_split2(char *c);

#endif
