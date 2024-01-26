NAME = philo
SRCS = check_arg.c  init_arg.c  main.c  philo.c  utils_0.c
OBJS = $(SRCS:.c=.o)
CFLAGS = 


all:$(NAME)

$(NAME):$(OBJS)
	gcc $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:clean
	rm -rf $(NAME)

re:fclean all