# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 18:52:56 by lamhal            #+#    #+#              #
#    Updated: 2024/08/12 10:35:55 by lamhal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc -g -fsanitize=address 
CFLAGS = -Wall -Werror -Wextra

SRC = parsing/parsing.c parsing/syntaxe_error.c utils/libft_utils.c \
	utils/linked_lst.c utils/linked_lst2.c parsing/env.c parsing/expand.c utils/libft_utils2.c \
	utils/linked_lst3.c parsing/handl_cmd.c utils/ft_split.c parsing/ambgus.c \
	parsing/expand_var.c parsing/remove.c parsing/token.c minishell.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)  
	$(CC) -o $@ $^ -lreadline


%.o: %.c minishell.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(BONUS)
	
re: fclean all

.PHONY: clean
