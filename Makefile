# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 13:41:39 by pesilva-          #+#    #+#              #
#    Updated: 2024/08/22 14:01:17 by pesilva-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

OBJS = ${SRC_FILES:.c=.o}
LIBFT = ./include/Libft
SRC_FILES = pipex.c \
			utils.c

HEADER = -Iincludes

CC = cc

CFLAGS = -Wall -Wextra -Werror

.c.o: %.o : %.c
	@cc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all: ${PROG}

${PROG}: ${OBJS}

				@echo "Compiling LIBFT"
				@make re -C ./libft

clean:
		@make clean -C ./libft
		@rm -f ${OBJS}

fclean: clean
				@make fclean -C ./libft
				@rm -f $(NAME)
				@rm -f ${PROG}

PHONY: all clean fclean