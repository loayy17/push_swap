CC = cc
CFLAGS = -Wall -Wextra -Werror $(INC)
AR = ar -rcs
RM = rm -f
NAME = push_swap
NAME_BONUS = checker
LIBFTDIR = libraries/Libft
LIBFT = $(LIBFTDIR)/libft.a
INC = -Iinclude -I$(LIBFTDIR)

SRC =   src/both_free.c \
		src/creations_sort_small.c \
		src/main.c \
		src/math_utils.c \
		src/sort_large.c \
		src/sort_large_utils.c \
		src/sort_utils.c \
		src/stack_utils.c \
		src/swap_operations.c \
		src/validations.c

SRC_BONUS = src_bonus/checker.c \
			src/both_free.c \
			src/creations_sort_small.c \
			src/math_utils.c \
			src/sort_large.c \
			src/sort_large_utils.c \
			src/sort_utils.c \
			src/stack_utils.c \
			src/swap_operations.c \
			src/validations.c


OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT)

all: $(NAME) $(NAME_BONUS)

$(LIBFT) :
	$(MAKE) -C $(LIBFTDIR)

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT) $(INC)

bonus: $(NAME_BONUS)

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re bonus