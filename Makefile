# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 13:58:53 by lrosch            #+#    #+#              #
#    Updated: 2022/01/18 16:57:42 by lrosch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC:=	gcc
NAME:=	philo.a
FLAGS:=	-Wall -Wextra -Werror
SRC:=	error_checking.c philo.c eat_sleep_repeat.c \
		philo_initialize.c free.c philo_utils.c edge_cases.c \
		thread.c

OBJECTS:= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@${CC} $(FLAGS) -c $(SRC)
	@ar rc $(NAME) *.o
	${CC} ${FLAGS} ${NAME} -o philo

clean:
	rm -f *.o

%.o: %.c
	@$(CC) $< -c $(FLAGS)

fclean: clean
	rm -f $(NAME)
	rm -f philo


re: fclean all
