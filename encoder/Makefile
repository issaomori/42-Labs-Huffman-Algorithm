NAME = encoder

CC = cc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE)

RM = rm -rf

PATH_SRC = ./src/
PATH_MAIN = $(PATH_SRC)main/
PATH_INIT = $(PATH_SRC)init/
PATH_UTILS = $(PATH_SRC)utils/
PATH_HUFFMAN_ALGORITHM = $(PATH_SRC)huffman_algorithm/
PATH_MEMORY_SHARED = $(PATH_SRC)memory_shared/

PATH_OBJS = ./objs/

SRC =	$(PATH_MAIN)main.c\
		$(PATH_INIT)init.c\
		$(PATH_UTILS)utils.c\
		$(PATH_HUFFMAN_ALGORITHM)compact.c\
		$(PATH_HUFFMAN_ALGORITHM)dicionary.c\
		$(PATH_HUFFMAN_ALGORITHM)encode.c\
		$(PATH_HUFFMAN_ALGORITHM)make_list.c\
		$(PATH_HUFFMAN_ALGORITHM)make_tree.c\
		$(PATH_HUFFMAN_ALGORITHM)read_text.c\
		$(PATH_MEMORY_SHARED)memory_shared.c\
		

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

$(PATH_OBJS)%.o:	$(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)main/
	@mkdir -p $(PATH_OBJS)init/
	@mkdir -p $(PATH_OBJS)utils/
	@mkdir -p $(PATH_OBJS)huffman_algorithm/
	@mkdir -p $(PATH_OBJS)memory_shared/
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) ./objs

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all $(PATH_OBJS) clean fclean re