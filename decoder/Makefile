NAME = decoder

CC = cc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE)

RM = rm -rf

PATH_SRC = ./src/
PATH_MAIN = $(PATH_SRC)main/
PATH_DESCOMPACT = $(PATH_SRC)descompact/
PATH_MEMORY_SHARED = $(PATH_SRC)memory_shared/

PATH_OBJS = ./objs/

SRC =	$(PATH_MAIN)main.c\
		$(PATH_DESCOMPACT)descompacted.c\
		$(PATH_MEMORY_SHARED)memory_shared.c\
		

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)main/
	@mkdir -p $(PATH_OBJS)descompact/
	@mkdir -p $(PATH_OBJS)memory_shared/
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) ./objs

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all $(PATH_OBJS) clean fclean re