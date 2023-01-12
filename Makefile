# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teliet <teliet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 20:41:39 by teliet            #+#    #+#              #
#    Updated: 2023/01/12 13:13:41 by teliet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c src/actions.c src/eating.c src/timers.c src/init.c \
lib/parser_utils.c lib/time_utils.c  src/free_all.c \

SRC_bonus = bonus/src/main.c bonus/src/actions.c bonus/src/eating.c bonus/src/timers.c bonus/src/init.c \
 bonus/lib/parser_utils.c  bonus/lib/time_utils.c  bonus/src/free_all.c bonus/src/errors.c \

CC = gcc

HEADERS = ./includes
HEADERS_bonus = ./bonus/includes

LIBS = 

OBJ = $(SRC:.c=.o)
OBJ_bonus = $(SRC_bonus:.c=.o)

all: ${NAME}
 
$(NAME): $(OBJ) $(LIBS) $(HEADERS)
	$(CC) $(OBJ) $(LIBS) -I $(HEADERS) -o $(NAME)

$(LIBS):
	make -C lib/ft_printf

#$(OBJ_bonus):$(SRC_bonus) $(HEADERS_bonus)
#	$(CC) -Wall -Wextra -Werror -I $(HEADERS_bonus) -c $< -o $@

bonus: $(SRC_bonus) $(LIBS) $(HEADERS_bonus)
	$(CC) $(SRC_bonus) $(LIBS) -I $(HEADERS_bonus) -g3 -o philo_bonus
	
debug: $(LIBS) $(HEADERS) clean
	$(CC) $(SRC) $(LIBS) -I $(HEADERS) -g3 -o $(NAME) # -fsanitize=thread

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I $(HEADERS) -c $< -o $@

clean:
	/bin/rm -f ${OBJ}
	/bin/rm -f ${OBJ_bonus}

fclean: clean
	/bin/rm -f ${NAME}

re: fclean all
