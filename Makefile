.SILENT:

NAME = philo
SRCS = main.c clean.c dead.c deadext.c init.c philo.c process.c routine.c thread.c external.c
OBJS = $(SRCS:.c=.o)

cc = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(RM) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)
	$(RM) $(OBJS)

re: fclean all