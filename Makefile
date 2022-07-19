# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 12:04:41 by nfukuma           #+#    #+#              #
#    Updated: 2022/07/19 12:05:32 by nfukuma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=

OBJS			= $(SRCS:.c=.o)

CC				= gcc
CPPFLAGS		+= -I./libft/
RM				= rm -f

NAME			=

all:			$(NAME)

$(NAME):		$(OBJS)
				make -C ./libft
				cp libft/libft.a $(NAME)
				ar rcs $@ $^

clean:
				make clean -C ./libft
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				make fclean -C ./libft
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:

.PHONY:			all clean fclean re
