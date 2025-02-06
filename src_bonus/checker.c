/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:00:00 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/06 18:45:01 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void execute_operation(t_node **a, t_node **b, char *instruction)
{
    if (!ft_strcmp(instruction, "pa"))
        push_stack(b, a, 'a',1);
    else if (!ft_strcmp(instruction, "pb"))
        push_stack(a, b, 'b',1);
    else if (!ft_strcmp(instruction, "ra"))
        rotate(a, 'a', 1);
    else if (!ft_strcmp(instruction, "rb"))
        rotate(b, 'b', 1);
    else if (!ft_strcmp(instruction, "rr"))
        rotate_both(a, b, 1);
    else if (!ft_strcmp(instruction, "rra"))
        reverse_rotate(a, 'a', 1);
    else if (!ft_strcmp(instruction, "rrb"))
        reverse_rotate(b, 'b', 1);
    else if (!ft_strcmp(instruction, "rrr"))
        reverse_rotate_both(a, b, 1);
    else if (!ft_strcmp(instruction, "sa"))
        swap(a, 'a', 1);
    else if (!ft_strcmp(instruction, "sb"))
        swap(b, 'b', 1);
    else if (!ft_strcmp(instruction, "ss"))
        swap_both(a, b, 1);
    else
    {
        free_resource(a, b);
        ft_dprintf(2, "Error\n");
        free(instruction);
        exit(1);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        ft_dprintf(2, "Error\n");
        return (1);
    }
    if (!validate_input(argv + 1))
    {
        ft_dprintf(2, "Error\n");
        return (1);
    }

    t_node *stack_a = create_stack(argv + 1);
    if (!stack_a)
    {
        ft_dprintf(2, "Error\n");
        return (1);
    }
    t_node *stack_b = NULL;
    long size_stack = get_stack_size(stack_a);

    char *line;
    while ((line = get_next_line(0)))
    {
        line[ft_strlen(line) - 1] = '\0';
        execute_operation(&stack_a, &stack_b, line);
        free(line);
    }
    if (is_sorted(stack_a) && !stack_b && get_stack_size(stack_a) == size_stack)
        ft_printf("OK\n");
    else
        ft_printf("KO\n");
    free_resource(&stack_a, &stack_b);
    return (0);
}
