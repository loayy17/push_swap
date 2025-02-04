CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFTDIR)
AR = ar -rcs
RM = rm -f
NAME = push_swap
NAME_BONUS = checker
LIBFTDIR = libraries/Libft
LIBFT = $(LIBFTDIR)/libft.a
SRC = src/main.c \
	  src/swap_operations.c \
	  src/free_resource.c \
	  src/creations.c \
	  src/ft_validation.c \
	  src/both_operations.c \
	  src/sort_large.c \
	  src/utils.c

SRC_BONUS = src_bonus/checker.c
INC = -Iincludes -I$(LIBFTDIR)

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT)

bonus: $(LIBFT) $(NAME_BONUS)

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