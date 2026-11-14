# El archivo que compila el programa:
# -make: compila los .c y crea rush-02
# -make clean: borra los .o
# -make fclean: borra los .o y rush-02
# -make re: lo borra todo y lo vuelve a compilar

NAME	= rush-02

SRCS	= main.c \
		  utils.c \
		  read_file.c \
		  parse_dict.c \
		  dict.c \
		  convert.c

OBJS	= $(SRCS:.c=.o)

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c rush02.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
