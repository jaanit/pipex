NAME    = pipex

CC      = gcc  
CFLAGS  = -Wall -Wextra -Werror


HEAD    = pipex.h
OBJS    = pipex.o ft_split.o libft.o child1.o child2.o error.o

all: $(NAME) $(HEAD)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(HEAD) 

clean:
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

