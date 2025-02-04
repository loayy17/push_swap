#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

typedef struct s_node
{
	int				data;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

int     ft_is_duplicated(char **str);
int     ft_is_all_number(char **str);
int     ft_is_number(char *str);
int     is_sorted(t_node *stack);
void	swap(t_node **stack, char a,int both);
void	push_stack(t_node **src, t_node **dest, char c);
void	rotate(t_node **stack, char c,int both);
void	reverse_rotate(t_node **stack, char c,int both);
void	swap_both(t_node **stack_a, t_node **stack_b);
void	rotate_both(t_node **stack_a, t_node **stack_b);
void	reverse_rotate_both(t_node **stack_a, t_node **stack_b);
int		get_stack_size(t_node *stack);
int		get_min(t_node *stack);
int		get_max(t_node *stack);
int		is_sorted(t_node *stack);
int		ft_is_number(char *str);
int		ft_is_all_number(char **str);
int		ft_is_duplicated(char **str);
int		validate_input(char **str);
t_node	*create_node(char *data);
t_node	*create_stack_a(char **str);
void	cleanup_nodes(t_node **stack);
void	free_resource(t_node **stack_a, t_node **stack_b);
void	sort_two(t_node **stack);
void	sort_three(t_node **stack);
void	sort_four(t_node **stack_a, t_node **stack_b);
void	sort_five(t_node **stack_a, t_node **stack_b);
void	sort_large(t_node **stack_a, t_node **stack_b);
void	sort_stack(t_node **stack_a, t_node **stack_b);
void		ft_quicksort(int *arr, int low, int high);
int			count_below_pivot(t_node *stack, int pivot);
int			find_position(t_node *stack, int value);
int			ft_abs(int num);
int			get_min(t_node *stack);
#endif
