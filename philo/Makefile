NAME = philo

SRCS =  main.c \
		parsing.c \
		init.c \
		supervisor.c \
		utils/ft_atoi.c \
		utils/get_time.c \
		utils/my_sleep.c \
		utils/ft_isdigit.c

FLAGS = -Wall -Werror -Wextra -lpthread#-fsanitize=address -g

all : $(NAME)

$(NAME) : $(SRCS)
	gcc -o $(NAME) $(FLAGS) $(SRCS)
	rm -rf $(NAME).dSYM
clean:

fclean:
	rm -f $(NAME)

re : fclean all