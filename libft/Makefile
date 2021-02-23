# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmorchid <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/11 08:53:02 by mmorchid          #+#    #+#              #
#    Updated: 2019/05/11 18:42:04 by mmorchid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

SRC = *.c

OBJ = *.o

CC_FLAGS = -c -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	@$(CC) $(CC_FLAGS) $(SRC)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re:     fclean all

