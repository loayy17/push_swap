/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <email@domain.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/02/04 23:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_chunk
{
	int				current;
	int				total;
	int				chunk_size;
	int				size;
	int				*sorted;
}					t_chunk;

typedef struct s_move
{
	int				best[2];
	int				best_cost;
	int				sizes[2];
}					t_move;

typedef struct s_node
{
	long			data;
	int				pos;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

void				swap(t_node **s, char c, int both);
void				push_stack(t_node **src, t_node **dst, char c,
						int not_print);
void				rotate(t_node **s, char c, int both);
void				reverse_rotate(t_node **s, char c, int both);
void				swap_both(t_node **stack_a, t_node **stack_b, int both);
void				rotate_both(t_node **a, t_node **b, int both);
void				reverse_rotate_both(t_node **a, t_node **b, int both);
int					get_stack_size(t_node *stack);
int					is_sorted(t_node *stack);
int					get_min(t_node *stack);
int					get_max(t_node *stack);
void				update_positions(t_node *stack);
int					ft_abs(int num);
int					is_valid_number(char *str);
int					check_duplicates(char **str);
int					validate_input(char **str);
int					*create_sorted_array(t_node *stack);
t_node				*create_node(char *data);
t_node				*create_stack(char **str);
void				free_stack(t_node **stack);
void				free_resource(t_node **stack_a, t_node **stack_b);
void				sort_two(t_node **stack);
void				sort_three(t_node **stack);
void				sort_large(t_node **a, t_node **b);
void				sort_stack(t_node **stack_a, t_node **stack_b);
void				ft_quicksort(int *arr, int low, int high);
int					find_min_position(t_node *a);
void				final_rotate(t_node **stack);
int					dynamic_chunk_count(int size);
void				move_from_a_to_b(t_node **a, t_node **b, int index,
						t_chunk *chunk);
void				push_chunks(t_node **a, t_node **b, int *sorted, int size);
int					get_target_position(t_node *a, int value);
int					check_empty_b(t_node *b, int *ca, int *cb);
void				update_best(t_node **a, t_node *tmp, t_move *move);
void				execute_operation(t_node **a, t_node **b,
						char *instruction);
#endif
