
NAME = 21sh
LIBFT_FILE = libft.a

LIBFT_DIR = ./libft
READLINE_DIR = ./src/readline
EXECUTION_DIR = ./src/execution
INC_DIR = ./includes/
LIBFT_INC = $(LIBFT_DIR)/
OBJ_DIR = ./obj

LFLAG = -ltermcap

LIBFT = $(LIBFT_DIR)/$(LIBFT_FILE)

HEADERS = $(INC_DIR)ft_readline.h $(INC_DIR)ft_execution.h

READLINE_FILES = ft_auto.c ft_calc.c ft_dir.c ft_handlers.c ft_history.c ft_history_2.c ft_init.c ft_mode.c ft_move.c ft_move_2.c ft_move_3.c ft_op.c ft_op_2.c ft_parse.c ft_prompt.c ft_prompt_2.c ft_quots.c ft_readline.c ft_select.c ft_signal.c ft_symbole.c ft_var.c ft_utils.c

EXECUTION_FILES = main4.c ft_alias.c builtins.c  data_from_env.c echo_command.c env.c error.c exexc.c free.c main.c pipe_semi.c prepar_to_exe.c redirection.c setenv_command.c ft_builtin_cd.c ft_builtin_alias.c ft_builtin_unalias.c ft_builtin_cd_2.c ft_path.c ft_path2.c error2.c exexc2.c pipe_semi2.c main2.c redirection2.c main3.c


LIBFT_SRC = $(addprefix $(LIBFT_DIR)/, $(LIBFT_FILES))
OBJ_READLINE = $(addprefix $(OBJ_DIR)/, $(READLINE_FILES:%.c=%.o))
OBJ_EXECUTION = $(addprefix $(OBJ_DIR)/, $(EXECUTION_FILES:%.c=%.o))

CC = gcc
CFLAGS = -g #-Wall -Werror -Wextra 
INC = -I $(INC_DIR) -I $(LIBFT_INC)

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

all: lib $(NAME)

$(OBJ_DIR)/%.o: $(READLINE_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)/%.o:  $(EXECUTION_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ_EXECUTION) $(OBJ_READLINE)
	@$(CC) $(OBJ_READLINE) $(OBJ_EXECUTION) $(LIBFT) $(LFLAG) -o $(NAME)
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

lib:
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@printf "21SH:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@rm -rf .21sh_history
	@rm -rf .21sh_alias
	@make -C $(LIBFT_DIR) fclean
	@printf "21SH:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all

