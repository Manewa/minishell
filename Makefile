# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: namalier <namalier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/11 16:29:28 by namalier          #+#    #+#              #
#    Updated: 2025/02/18 12:28:19 by namalier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ENV				= srcs/Parsing/env
TOKENS			= srcs/Parsing/tokenization
UTILS			= srcs/Parsing/utils
EXEC_TYPE		= srcs/Parsing/exec_type
OBJDIR 			= obj
LIBA			= includes/Libft/libft.a

SRCS 			=	srcs/main.c srcs/init_prompt.c ${ENV}/env.c \
					${TOKENS}/tokenization.c ${TOKENS}/expand.c \
					${TOKENS}/token_line.c ${TOKENS}/tokens_for_exec.c \
					${EXEC_TYPE}/exec_append.c ${EXEC_TYPE}/exec_word.c \
					${EXEC_TYPE}/exec_heredoc.c ${EXEC_TYPE}/exec_inredir.c \
					${EXEC_TYPE}/exec_outredir.c ${EXEC_TYPE}/count_array.c\
					${UTILS}/quotes.c ${UTILS}/quotes_remover.c \
					${UTILS}/utils_lst.c ${UTILS}/utils_lst2.c \
					${UTILS}/utils_parsing.c ${UTILS}/ft_error.c \
					${UTILS}/split_off_quote.c \

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

${OBJDIR}/%.o	: ${EXEC_TYPE}/%.c
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
