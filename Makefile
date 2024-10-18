# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namalier <namalier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 16:29:28 by namalier          #+#    #+#              #
#    Updated: 2024/10/18 16:35:56 by namalier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSING			= srcs/Parsing
EXEC			= srcs/Exec
OBJDIR 			= obj
LIBA			= includes/Libft/libft.a

SRCS 			=	srcs/main.c srcs/init_prompt.c srcs/env.c \

OBJS 			=	$(patsubst %.c,${OBJDIR}/%.o,$(notdir ${SRCS}))

NAME			=	minishell

CFLAGS			=	-Wall -Werror -Wextra -g3

${NAME}			:	${OBJDIR} ${OBJS} ${LIBA}
					cc ${OBJS} ${LIBA} ${CFLAGS} -o ${NAME} -lreadline

$(OBJDIR)		:
				@mkdir -p $@

%.o: srcs/%.c
	cc ${CFLAGS} -c $< -o $@

${OBJDIR}/main.o	: srcs/main.c
				cc ${CFLAGS} -c $< -o $@

${OBJDIR}/%.o	: srcs/%.c
				cc ${CFLAGS} -c $< -o $@

${LIBA}			:
				make -C includes/Libft

clean			:
				rm -rf ${OBJDIR} includes/Libft/objs

fclean			:	clean
				rm -rf ${NAME} includes/Libft/libft.a

re				: fclean all

all				: 	${NAME}

.PHONY			: all clean fclean re
