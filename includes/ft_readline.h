/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:47:03 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/31 15:37:18 by mmorchid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <pwd.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include "../libft/includes/libft.h"

# define TERM "xterm-256color"
# define BUFF_SIZE 32
# define C_RED "\x1B[31m"
# define C_GRN "\x1B[32m"
# define C_YEL "\x1B[33m"
# define C_BLU "\x1B[34m"
# define C_MAG "\x1B[35m"
# define C_CYN "\x1B[36m"
# define C_WHT "\x1B[37m"
# define C_RESET "\x1B[0m"
# define C_SELECT "\x1B[1;37;41m"
# define C_AUTOSELECT "\x1B[0;4;30;43m"
# define MAX_BUFF 1024
# define K_LEFT 4479771
# define K_RIGHT 4414235
# define K_BACKSPACE 127
# define K_DEL 2117294875
# define K_ENTER 10
# define K_HOME 4741915
# define K_END 4610843
# define K_UP 4283163
# define K_DOWN 4348699
# define K_ALTV 10127586
# define K_ALTC 42947
# define K_ALTS 40899
# define K_ALTX 8948194
# define K_ALTRIGHT 1130044187
# define K_ALTLEFT 1146821403
# define K_ALTUP 1096489755
# define K_ALTDOWN 1113266971
# define K_COPYBEFORE 10783202
# define K_COPYAFTER 10848738
# define K_CTRLD 4
# define K_TAB 9
# define B_HELP 1
# define B_ECHO_S_N 2
# define B_ECHO_S_E 4
# define B_ECHO_B_E 8
# define B_UNSETENV_S_M 2
# define B_UNALIAS_S_M 2
# define B_ALIAS_S_L 2
# define B_ENV_S_U 2
# define B_ENV_S_I 4
# define O_NONE 0
# define O_SEMICOLON 1
# define O_PIPE 2
# define O_AND 16
# define O_OR 32
# define O_BG 64
# define M_INSERT 1
# define M_OTHER 0
# define F_AL ".minishell_alias"
# define F_H ".minishell_history"

typedef struct			s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
}						t_var;

typedef struct			s_di
{
	char			*name;
	struct s_di		*next;
}						t_di;

typedef struct			s_his
{
	char			*line;
	char			*dis_line;
	int				type;
	int				cur;
	int				id;
	struct s_his	*next;
	struct s_his	*prev;
}						t_his;

typedef struct			s_alias
{
	char			*alias;
	char			*str;
	struct s_alias	*next;
}						t_alias;

typedef struct			s_env
{
	char			*gnl;
	t_var			*var;
	size_t			line_len;
	int				row;
	int				col;
	int				cur_row;
	int				cur_col;
	int				cur_all_col;
	int				cur_all_row;
	int				last_char_col;
	int				last_char_row;
	int				org_cur_x;
	int				org_cur_y;
	int				cur_mult_col;
	char			*prompt;
	char			*home;
	size_t			prompt_len;
	size_t			multi_prompt_len;
	t_his			*his;
	t_alias			*al;
	char			*username;
	char			*hostname;
	char			*branch;
	size_t			branch_len;
	char			*working_dir;
	char			*old_working_dir;
	int				select_mode;
	int				select_pos;
	int				select_char;
	char			*select_line;
	pid_t			current_pid;
	int				com_pipe;
	int				*fd_pipe;
	int				rw_pipe[3];
	char			*auto_com;
	int				auto_step;
	int				auto_select;
	size_t			auto_len;
	char			*line;
	int				num;
	int				res_stdin;
	int				res_stdout;
	int				res_stderr;
	struct termios	org_tattr;
	int				running_proc;
	int				inside_prompt;
}						t_env;

typedef struct			s_com
{
	char	**args;
	t_var	*var;
	char	*param;
	int		p_param;
	int		type;
	int		start;
	int		arg_start;
}						t_com;

typedef struct			s_path
{
	char			*line;
	struct s_path	*next;
	struct s_path	*prev;
}						t_path;

typedef struct			s_line
{
	long long		op_main;
	t_com			com;
	int				fd;
	int				ret;
	int				status;
	pid_t			pid;
	char			*path;
	struct s_line	*next;
	struct s_line	*prev;
}						t_line;

t_env					g_env;

t_var					*ft_new_env_var(char *key, char *value);
void					ft_add_env_var(t_var **head, t_var *new);
t_var					*ft_load_env(char **envp);
void					ft_free_var(t_var **head);
char					*ft_free_strjoin(char *str1, char *str2);
void					ft_get_prompt(void);
void					ft_move_right(char *line, int mode);
void					ft_move_left(char *line, int mode);
void					ft_move_up(char **line);
void					ft_move_down(char **line);
void					ft_move_home(char *line, int start);
void					ft_move_end(char *line, int start);
void					ft_word_left(char *line);
void					ft_word_right(char *line);
void					ft_line_down(char **line);
void					ft_line_up(char **line);
void					ft_init(char **envp);
void					ft_set_input_mode(void);
void					ft_get_cursor_coor(int *x, int *y);
void					ft_putstr_char(char c, char **line);
void					ft_delete(char **line);
void					ft_backspace(char **line);
int						ft_parse(char **line);
char					*ft_readline();
char					*ft_get_var_value(t_var *head, char *key);
char					**ft_escape_strsplit(char const *s, char c);
void					ft_save_his(char *line, int type);
void					ft_save_alias(t_alias **al, char *alias, char *str);
void					ft_putline(char *line, int pos, int mode);
void					ft_toggle_select(char *line);
void					ft_cut_line(char **line);
void					ft_copy_line(char **line);
void					ft_paste_line(char **line);
int						ft_parse_param(t_com *com, char *charset);
int						ft_check_builtin(char *name, t_com *com);
void					ft_ext_builtin(t_line *line);
void					ft_parse_command(char *line, t_com *com);
t_path					*ft_new_path(char *path);
void					ft_pushback_path(t_path **head, t_path *new);
void					ft_add_path(t_path **head, t_path *new);
void					ft_populate_path_list(t_path **head,
char **split, int mode);
void					ft_remove_last_path(t_path **head);
char					*ft_join_path(t_path *path);
void					ft_free_path(t_path **head);
void					ft_setenv_var(t_var **var, char *key, char *value);
void					ft_add_alias(t_alias **head, t_alias *new);
t_alias					*ft_new_alias(char *alias, char *str);
int						ft_cd_ret_err(char *path);
void					ft_signal_handle(void);
void					ft_size_init();
void					ft_tononprint(char **str);
void					ft_pushback_line(t_line **head, t_line *new);
t_line					*ft_new_line(t_com com, int op);
void					ft_parse_command_line(t_line **head, char *line);
t_di					*ft_new_dir(char *name);
void					ft_add_dir(t_di **head, t_di *new);
void					ft_free_dir(t_di **head);
t_di					*ft_load_dir(char *var);
void					ft_auto_list_file(char *name, int dir, char **line);
int						ft_auto_check_file(char *name, char **line, int dir);
char					**ft_dir_to_tab(char *name,
t_di *di, int *wide, int size);
void					ft_auto_list_env(char *name, char **line);
int						ft_auto_check_env(char *name, char **line);
char					**ft_var_to_tab(char *name,
t_var *var, int *wide, size_t *size);
void					ft_auto_process(char **line);
char					*ft_auto_get_path(char *name);
void					ft_autocompletion(char **line);
char					*ft_decode_line(char *str);
char					*ft_encode_line(char *str);
char					ft_decode_char(char c);
void					ft_store_his();
void					ft_store_alias();
void					ft_load_his();
void					ft_load_alias();
void					ft_push_his(t_his **head, t_his *new);
void					ft_check_alias(char **line);
void					ft_exec_exit();
void					ft_unset_input_mode(void);
void					ft_reset_input_mode(void);
char					**ft_get_envp(t_var *head);
void					ft_free_table(char ***table);
char					*ft_exec_line(t_line *tmp);
void					ft_exec_clear();
void					ft_exec_builtin(t_line *line);
void					ft_echo_param(t_com *com);
void					ft_cd_param(t_com *com);
void					ft_setenv_param(t_com *com);
void					ft_unsetenv_param(t_com *com);
void					ft_env_param(t_com *com);
void					ft_alias_param(t_com *com);
void					ft_unalias_param(t_com *com);
void					ft_ext_cd(t_line *line);
void					ft_ext_setenv(t_line *line);
void					ft_ext_unsetenv(t_line *line);
void					ft_ext_env(t_line *line);
void					ft_ext_alias(t_line *line);
void					ft_ext_unalias(t_line *line);
void					ft_ext_echo(t_line *line);
void					ft_exec_check_path(char *wd, t_line *line, char **path);
void					ft_exec_check_env(t_var *var,
t_line *line, char **path);
void					ft_free_env();
int						get_next_line(const int fd, char **line);
void					ft_free_line(t_line **head);
void					ft_echo_help(void);
void					ft_env_help(void);
void					ft_setenv_help(void);
void					ft_alias_help(void);
void					ft_unalias_help(void);
void					ft_unsetenv_help(void);
void					ft_cd_help(void);
int						ft_getcwd(char *path);
int						ft_echo_char(int c);
void					ft_exec_env_arg(t_line *line);
//----------------------
t_his					*ft_new_his(char *line, int type);
int						ft_exe_ret_err(char *path);
void					ft_encode_char(char *pos, int type);
void					ft_manage_quots(char **line, char **copy);
void					ft_check_users(char **val, char *user, int *i);
void					ft_manage_symbol(char **line);
void					ft_enter(void);
void					ft_controle_d(char **line);
void					ft_get_git_branch(char *pwd);
int						ft_isnonprint(char c);
void					ft_manage_newline(char **line, char **copy);

#endif
