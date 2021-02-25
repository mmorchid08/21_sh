
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
LIBFT_HEADERS = $(LIBFT_INC)libft.h $(LIBFT_INC)get_next_line.h

READLINE_FILES = ft_alias.c ft_auto.c ft_calc.c ft_dir.c ft_handlers.c ft_history.c ft_history_2.c ft_init.c ft_mode.c ft_move.c ft_move_2.c ft_move_3.c ft_op.c ft_op_2.c ft_parse.c ft_prompt.c ft_prompt_2.c ft_quots.c ft_readline.c ft_select.c ft_signal.c ft_symbole.c ft_var.c ft_utils.c

EXECUTION_FILES = builtins.c cd_command.c cd_command_sequel.c data_from_env.c echo_command.c env.c error.c exexc.c free.c main.c pipe_semi.c prepar_to_exe.c redirection.c setenv_command.c

LIBFT_FILES = ft_atoi.c ft_bzero.c ft_del.c ft_ifcount.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_islower.c ft_isprint.c ft_isupper.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstlen.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memindex.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_strindex.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strreplace.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c get_next_line.c

LIBFT_SRC = $(addprefix $(LIBFT_DIR)/, $(LIBFT_FILES))
OBJ_READLINE = $(addprefix $(OBJ_DIR)/, $(READLINE_FILES:%.c=%.o))
OBJ_EXECUTION = $(addprefix $(OBJ_DIR)/, $(EXECUTION_FILES:%.c=%.o))

CC = gcc
CFLAGS = #-Wall -Werror -Wextra 
INC = -I $(INC_DIR) -I $(LIBFT_INC)

C_RED = \033[31m
C_GREEN = \033[32m
C_CYAN = \033[36m
C_NONE = \033[0m

all: $(NAME)

$(LIBFT_FILE):
	@make -C $(LIBFT_DIR)
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)/%.o: $(READLINE_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR)/%.o:  $(EXECUTION_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@

$(NAME): $(OBJ_DIR) $(OBJ_EXECUTION) $(OBJ_READLINE)
	@make -C $(LIBFT_DIR)
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" "libft.a"
	@$(CC) $(OBJ_READLINE) $(OBJ_EXECUTION) $(LIBFT) $(LFLAG) -o $(NAME)
	@printf "21SH:  %-25s$(C_GREEN)[done]$(C_NONE)\n" $@


clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@printf "21SH:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@printf "21SH:  %-25s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all

