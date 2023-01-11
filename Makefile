# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teliet <teliet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 20:41:39 by teliet            #+#    #+#              #
#    Updated: 2023/01/11 15:17:39 by teliet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c src/actions.c src/eating.c src/timers.c src/init.c \
lib/parser_utils.c lib/time_utils.c  src/free_all.c \

SRC_bonus = bonus/main.c bonus/actions.c bonus/eating.c bonus/timers.c bonus/init.c \
lib/parser_utils.c lib/time_utils.c  bonus/free_all.c \

CC = gcc

HEADERS = -I ./includes

LIBS = 

OBJ = $(SRC:.c=.o)
OBJ_bonus = $(SRC_bonus:.c=.o)

all: ${NAME}
 
$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBS):
	make -C lib/ft_printf

bonus: $(OBJ_bonus) $(LIBS)
	$(CC) $(OBJ_bonus) $(LIBS) $(HEADERS) -o philo_bonus

	
debug: $(LIBS) clean
	$(CC) $(SRC) $(LIBS) $(HEADERS) $(LFLAGS) -g3 -o $(NAME) # -fsanitize=thread

%.o: %.c
	$(CC) -Wall -Wextra -Werror $(HEADERS) -c $< -o $@

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f ${NAME}

re: fclean all
