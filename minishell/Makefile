NAME = minishell
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -O2
LFLAGS = -lreadline -L/Users/yakhoudr/lib
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
