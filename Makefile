# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: obult <obult@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/19 12:29:04 by obult         #+#    #+#                  #
#    Updated: 2022/02/06 17:00:01 by obult         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= philo
OBJ			= main.o ph_input.o ph_atoi.o philo.o start_sim.o time.o eat_sleep_think.o forks.o
OBJS		= $(addprefix obj/, ${OBJ})
CC			= gcc
RM			= rm -f
HEADER		= -I headers/
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address

all:		${NAME}

obj/%.o:	src/%.c
				@mkdir -p $(dir $@)
				@$(CC) -c $(CFLAGS) $(HEADER) -o $@ $<

clean:
				@${RM} ${OBJS}
				$(info ************  Pilo Clean)

fclean:		clean
				@${RM} ${NAME}
				$(info ************  Pilo Removed) 

re:			fclean all

${NAME}:	${OBJS}
				@${CC} ${CFLAGS} -o $@ $^
				$(info ************  Pilo Ready!)

.PHONY: all clean fclean re libft