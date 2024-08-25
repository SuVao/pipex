# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 13:41:39 by pesilva-          #+#    #+#              #
#    Updated: 2024/08/25 18:18:53 by pesilva-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

OBJS = ${SRC_FILES:.c=.o}
LIBFT_DIR = ./Libft/
SRC_FILES = pipex.c \
			utils.c

HEADER = -Iincludes

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = $(LIBFT_DIR)libft.a

%.o: %.c
	@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS} $(LIBFT)
	echo "Compiling LIBFT"
	make re -C ${LIBFT_DIR}
	${CC} ${CFLAGS} ${OBJS} -L${LIBFT_DIR} -lft -o ${NAME}

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	make clean -C ${LIBFT_DIR}
	rm -f ${OBJS}
	rm -f ${NAME}

fclean: clean
	make fclean -C ${LIBFT}
	rm -f ${OBJS}
	rm -f ${NAME}

re: fclean $(LIBFT) all

.PHONY: all clean fclean re