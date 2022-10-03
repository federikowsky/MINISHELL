# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 09:56:09 by agenoves          #+#    #+#              #
#    Updated: 2022/10/04 00:22:58 by fefilipp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell
CC = 			gcc
LIBFT = 		libft/libft.a
CFLAGS = 		-Wall -Werror -Wextra -g
READLINE = 		-L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
RM = 			rm -rf

FILES = 		sources/main \
				sources/cd \
				sources/env \
				sources/pipe \
				sources/bonus \
				sources/export \
				sources/parser \
				sources/signal \
				utils/utils \
				utils/utils2 \
				utils/utilsToken \
				utils/utilsToken2 \
				utils/utilsToken3 \
				# sources/builtin \
				# sources/pwd \
				# sources/cmd_exec \
				# sources/echo \
				# sources/unset \
				# sources/pipe \
				# utils/utils
				
SOURCES_DIR =	./
SOURCES = 		$(addprefix $(SOURCES_DIR), $(addsuffix .c, $(FILES)))
OBJECTS =		${SOURCES:.c=.o}

HEADER = 		${SOURCES_DIR}includes/minishell.h

${NAME}:
	@make -s -C libft
	${CC} ${CFLAGS} ${READLINE} ${SOURCES} $(LIBFT) -o $@

all: ${NAME} 
${NAME}: ${OBJECTS}

clean: 
	@make -s -C libft clean	
	@echo "Libft cleaned successfully"
	@${RM} ${OBJECTS}
	@echo "Minishell cleaned successfully"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
