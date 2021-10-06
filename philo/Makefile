NAME = philo

SRCS =  main.c \
		parsing.c \
		utils/ft_atoi.c \
		utils/get_time.c \
		utils/my_sleep.c \
		utils/ft_isdigit.c

FLAGS = -Wall -Werror -Wextra -g -fsanitize=address 

all : $(NAME)

$(NAME) :
	gcc -o $(NAME) $(FLAGS) $(SRCS)
	rm -rf $(NAME).dSYM
clean:

fclean:
	rm -f $(NAME)

re : fclean all