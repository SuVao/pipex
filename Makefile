# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 13:41:39 by pesilva-          #+#    #+#              #
#    Updated: 2024/08/24 19:10:51 by pesilva-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

OBJS = ${SRC_FILES:.c=.o}
LIBFT = ./Libft
SRC_FILES = pipex.c \
			utils.c

HEADER = -Iincludes

CC = cc

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	echo "Compiling LIBFT"
	make re -C ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} -I${LIBFT} -o ${NAME}

clean:
	make clean -C ${LIBFT}
	rm -f ${OBJS}
	rm -f ${NAME}

fclean: clean
	make fclean -C ${LIBFT}
	rm -f ${OBJS}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re