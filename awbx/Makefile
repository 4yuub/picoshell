# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yakhoudr <yakhoudr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 14:28:23 by yakhoudr          #+#    #+#              #
#    Updated: 2022/08/03 14:28:23 by yakhoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADERS = minishell.h
SRCS = debug.c env.c lists.c main.c parser.c str_utils.c tokenizer.c tokenizer_utils.c
OBJS := $(SRCS:.c=.o)
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
