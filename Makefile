CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(LIBFTDIR) -g
AR = ar -rcs
RM = rm -f
NAME = push_swap
NAME_BONUS = checker
LIBFTDIR = libraries/Libft
LIBFT = $(LIBFTDIR)/libft.a
SRC = src/creations_sort_small.c \
	  src/both_free.c \
	  src/main.c \
	  src/sort_large.c \
	  src/sort_utils.c \
	  src/stack_utils.c \
	  src/swap_operations.c \
	  src/validations.c

SRC_BONUS = src_bonus/checker.c \
			src/creations_sort_small.c \
			src/both_free.c \
			src/sort_large.c \
			src/sort_utils.c \
			src/stack_utils.c \
			src/swap_operations.c \
			src/validations.c
INC = -Iincludes -I$(LIBFTDIR)

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT)

bonus: $(LIBFT) $(NAME) $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT) $(INC)

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re bonus