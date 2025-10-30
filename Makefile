CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
NAME = philo

INCLUDES = -Iincludes

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
endif

ifeq ($(HELGRIND), 1)
	CFLAGS += -g3 -O0
endif

SRC = src/main.c
SRC += src/init.c
SRC += src/init_helpers.c
SRC += src/parser.c
SRC += src/parser_utils.c
SRC += src/utils.c
SRC += src/cleanup.c
SRC += src/monitor.c
SRC += src/philosopher.c
SRC += helpers/ft_atoi_safe.c
SRC += helpers/ft_isspace.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "philo compiled successfully"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
