# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namalier <namalier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 16:29:28 by namalier          #+#    #+#              #
#    Updated: 2025/01/28 14:11:18 by natgomali        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ENV				= srcs/Parsing/env
TOKENS			= srcs/Parsing/tokenization
UTILS			= srcs/Parsing/utils
EXEC			= srcs/Exec
OBJDIR 			= obj
LIBA			= includes/Libft/libft.a

SRCS 			=	srcs/main.c srcs/init_prompt.c ${ENV}/env.c \
					${TOKENS}/tokenization.c ${TOKENS}/expand.c \
					${TOKENS}/token_line.c ${TOKENS}/token_quotes.c \
					${UTILS}/utils_lst.c ${UTILS}/utils_parsing.c \
					${UTILS}/ft_error.c ${UTILS}/split_off_quote.c \

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

${OBJDIR}/init_prompt.o	: srcs/init_prompt.c
				cc ${CFLAGS} -c $< -o $@

${OBJDIR}/%.o	: ${ENV}/%.c
				cc ${CFLAGS} -c $< -o $@

${OBJDIR}/%.o	: ${TOKENS}/%.c
				cc ${CFLAGS} -c $< -o $@

${OBJDIR}/%.o	: ${UTILS}/%.c
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
