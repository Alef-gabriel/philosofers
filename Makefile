NAME = philo

CC = gcc

CFLAGS	= -Wall -Wextra -Werror

RM = rm -rf

INCLUDE = -pthread

PATH_SRC = ./
PATH_OBJS = ./objs/

SRCS = $(PATH_SRC)checker.c $(PATH_SRC)init.c $(PATH_SRC)parce.c \
	$(PATH_SRC)philosophers.c $(PATH_SRC)utils.c $(PATH_SRC)clean.c

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) ./objs/*.o -o $(NAME)

$(PATH_OBJS)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -pthread -c $< -o $@

clean:
	@echo "\033[1;33mCleaning objects\033[0m"
	@$(RM) $(PATH_OBJS)
	@echo "\033[1;32mDone!\033[0m"

fclean: clean
	@$(RM) philo
	@echo  "\033[1;33mCleaning all\033[0m"

re: fclean all

.PHONY: all clean fclean re push