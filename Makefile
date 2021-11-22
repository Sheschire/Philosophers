# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:16:17 by tlemesle          #+#    #+#              #
#    Updated: 2021/10/26 16:17:34 by tlemesle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= srcs/main.c\
				  srcs/utils.c\
				  srcs/simulation.c\
				  srcs/simulation_utils.c\
				  srcs/time_utils.c\
				  srcs/init.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I./includes -fsanitize=thread
PTHREAD			= -lpthread

NAME			= philo

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${PTHREAD}

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re