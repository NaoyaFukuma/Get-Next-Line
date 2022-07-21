# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 12:04:41 by nfukuma           #+#    #+#              #
#    Updated: 2022/07/21 16:34:05 by nfukuma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= get_next_line.c get_next_line_utils.c main.c

OBJS			= $(SRCS:.c=.o)

CPPFLAGS		+= -Wall -Wextra -Werror
RM				= rm -f

NAME			= a.out

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc $(OBJS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
