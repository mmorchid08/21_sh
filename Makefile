# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmorchid <mmorchid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 10:30:51 by mmorchid          #+#    #+#              #
#    Updated: 2021/02/09 16:19:02 by mmorchid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = 21_sh

LIBFT = libft/libft.a

#CFLAGS = -Wall -Wextra -Werror

FILES = main.c pipe_semi.c builtins.c echo_command.c redirection.c data_from_env.c env.c setenv_command.c cd_command.c cd_command_sequel.c prepar_to_exe.c free.c exexc.c error.c
CC = gcc

all: $(NAME)

$(NAME) : $(FILES:.c=.o)
	@make -C libft
	@$(CC) $(FILES) $(LIBFT) $(CFLAGS) -I 21_sh.h -I libft/ -o $(NAME)


clean:
	@make clean -C libft
	@rm -f $(FILES:.c=.o)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
