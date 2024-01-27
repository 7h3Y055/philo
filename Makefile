NAME = philo
SRCS = check_arg.c  init_arg.c  main.c  philo.c  utils_0.c utils_1.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -g -g3  #-Wall -Werror -Wextra


all:$(NAME)

$(NAME):$(OBJS)
	gcc $(OBJS) -no-pie $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:clean
	rm -rf $(NAME)

re:fclean all
