NAME = philosopher
CC = cc
FLAGS = -Wall -Wextra -Werror 
FILE =  main.c simulation.c philosopher.c parsing.c helper_function.c sumilation_function.c init_struct.c monitor.c
OBJ = $(FILE:.c=.o)

all : $(NAME)
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -pthread 
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -f $(NAME)
re : fclean all