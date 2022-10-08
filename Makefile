# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 09:56:09 by agenoves          #+#    #+#              #
#    Updated: 2022/10/08 18:57:08 by fefilipp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell
CC = 			gcc
LIBFT = 		libft/libft.a
CFLAGS = 		 -g
READLINE = 		-L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include
RM = 			rm -rf

FILES = 		sources/main \
				sources/cd \
				sources/env \
				sources/pwd \
				sources/echo \
				sources/pipe \
				sources/exit \
				sources/bonus \
				sources/unset \
				sources/parser \
				sources/signal \
				sources/export  \
				sources/exec_cmd \
				sources/newshell \
				sources/redirections \
				utils/utils \
				utils/utils2 \
				utils/utilsToken \
				utils/utilsToken2 \
				utils/utilsToken3 \
				utils/utilsToken4 \
				# sources/builtin \
				# sources/cmd_exec \
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
	@make -s -C libft fclean	
	@echo "Libft cleaned successfully"
	@${RM} ${OBJECTS}
	@echo "Minishell cleaned successfully"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
