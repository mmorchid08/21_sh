
#ifndef FT_EXECUTION_H
# define FT_EXECUTION_H

#include "ft_readline.h"
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define REDIRECTION_RIGHT 1 // >
#define REDIRECTION_LEFT 2// <
#define REDIRECTION_LEFT_LEFT 3 // <<
#define REDIRECTION_LEFT_LEFT_LEFT 7 // <<<
#define REDIRECTION_RIGHT_RIGHT 4 // >>
#define REDIRECTION_RIGHT_AGGREGATION 5  // >& 
#define ESPACE_REDIRECTION_RIGHT_AGGREGATION 55  // >& 
#define REDIRECTION_LEFT_AGGREGATION 6  // <& 
// #define REDIRECTION_AGGREGATION_RIGHT 7  // &>
#define PRE_AGGREGATION_NUMBER 17
#define AND 8  // &&
#define OR 9  // ||
#define PIPE 10 // |
#define SEMICOLON 11 // ;
#define AMP 12 // &
#define REDIRECTION_WORD 13  // redirection + word
#define WORD_REDIRECTION 14  //  word + redirection 
#define WORD_REDIRECTION_ESPACE 16  //  word + redirection espace is like word
#define WORD 0 // &
#define READ_END 0
#define WRITE_END 1
#define ERROR_END 2
#define NUMBER_OF_STRING 7
#define MAX_STRING_SIZE 15

#define SPACE 15
// #define TABULATION  16

typedef struct  s_tokens
{
    char    *data;
    int     type;
    char    *here;
    int      space_b;
    struct  s_tokens *next;
}               t_tokens;

typedef	struct			s_list_path
{
	char				*name_path;
	struct s_list_path	*next;
}						t_list_path;

typedef struct s_data_env
{
    char *key;
    char *value;
}               t_data_env;


typedef struct s_content
{
    int index;
    int type;
}               t_content;

//list for list to spilt for pipe |
typedef struct s_pipe
{
    char *data;
    int type;
    struct s_pipe *next;

}               t_pipe;
//list for list to spilt for semiclone ;

typedef struct s_semi
{
    t_tokens *begin;
    t_tokens *finish;
    struct s_semi *next;
}               t_semi;

typedef struct s_fd
{
    int fd_old[2];
    int fd_new[2];
}               t_fd;


t_tokens *handling(char *line);
void handling_semi(t_tokens *tokens);
void handling_pipe(t_tokens *start,t_tokens *list);
void handling_command(t_tokens *begin,t_tokens *finish, t_fd fd, int pos, int count_pipe);
t_semi *new_node_semi(char *data, int type);
t_tokens *new_node(char *data, int type);

/* the execatble function */
int		ft_check_builtins(char *table);
void	ft_verify_builtins(t_tokens * token_begin, t_tokens *token_finish);
void	ft_operation_echo(t_tokens *token_begin, t_tokens * token_finish);

/*  redection function and prepare argv     */
void redirection_out(char *file_name, int fd);
void redirection_out_out(char *file_name, int fd);
void redirection_in(char *file_name, int fd);
char **prepere_argv(t_tokens *begin,t_tokens *finish);
int ft_count(t_tokens *begin, t_tokens *finish);
void redirection(t_tokens *begin, t_tokens *finish);

/* echo function  */
int		ft_chek_espace(char *buf);

/*    this for envirement */
void		ft_env_list(char **env);
// printenv 
void	ft_env_function(void);
void	free_list_env(void);
//setenv 
void	ft_add_to_env(t_data_env data_env);
void	ft_cat_new_env_to_key_value(t_data_env *data_env, char *buf);
void	ft_add_change_env(t_tokens *token_begin);
void	ft_delete_one_env(t_tokens *token_begin, t_tokens *token_finish);

/* cd and what he want  */
void	ft_operation_cd(t_tokens *token_begin,t_tokens *token_finish);
char	*ft_get_home(void);
char	*ft_get_pwd(void);
char	*ft_get_old_pwd(void);
void	ft_tack_pwd(void);
void	ft_the_current(char *path);
void	ft_tilda(char *value, int len);
void	ft_write_path(char *value);
void	ft_work_hyphen(char *token);

/*  function for exection anad open path aml the things */
void	exection(char *binary, char **argv, char **env);

t_list_path	*get_malloc_value_path(char *value);

char	*ft_read_from_dir(t_list_path *tmp2, t_tokens *token_begin);
void	ft_path_list(char *path_str,t_list_path **path_list);
char	*open_paths(t_tokens *begin, t_list_path	**path_list);
void ft_exece(t_tokens *begin, t_tokens *finish); 
// prepare 
char	**ft_convert_list_env_array(void);
char	**ft_convert_list_array(t_tokens *token_begin, t_tokens *token_finish);
int		ft_count_env(void);
int		ft_count_tokens(t_tokens *token_begin , t_tokens *token_finish);

// free
void	free_list_token(t_tokens **token);
void	free_list_path(t_list_path **path);

//error
void	ft_check_error(char *name);
int ft_check_multi_semi(t_tokens *tmp);
int ft_check_multi_pipe(t_tokens *tmp);
int  ft_check_bad_fd(t_tokens *tmp);
int  ft_error_parse(t_tokens *tmp);
int ft_know_type(t_tokens *tmp);

//authorization for file discriptor 
  int authorization_re(t_tokens *token); 
t_var	*get_malloc_key_value(char *key, char *value);

void ft_heredoc(char *line);
void ft_herestr(char *line);
int ft_get_type(char *c, int offset);

#endif