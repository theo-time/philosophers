# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teliet <teliet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 20:41:39 by teliet            #+#    #+#              #
#    Updated: 2023/01/06 18:16:51 by teliet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c src/actions.c lib/utils.c  \

CC = gcc

HEADERS = -I ./includes

LIBS = 

OBJ = $(SRC:.c=.o)

all: ${NAME}
 
$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBS):
	make -C lib/ft_printf
	
debug: $(LIBS) clean
	$(CC) $(SRC) $(LIBS) $(HEADERS) $(LFLAGS) -g3 -fsanitize=thread -o $(NAME) 

%.o: %.c
	$(CC) -Wall -Wextra -Werror $(HEADERS) -c $< -o $@

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f ${NAME}

re: fclean all
