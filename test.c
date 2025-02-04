/*
    push_swap.c
    ------------
    A complete solution for the push_swap project.
    It implements allowed operations:
      sa, sb, ss, ra, rb, rr, rra, rrb, rrr, pa, pb.
    It validates input (numbers only, no duplicates), creates a doubly–linked list,
    and uses optimized sorting routines:
      - For 2, 3, 4, or 5 numbers, simple routines.
      - For larger inputs (e.g. 500 numbers) an optimized chunk–based algorithm
        is used that selects the best candidate (minimal rotations) and uses combined
        rotations (rr, rrr) when possible.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>

/* =======================================================
   Basic printing functions (minimal replacements)
   ======================================================= */
void    ft_printf(const char *format, ...){
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void    ft_dprintf(int fd, const char *format, ...){
    va_list args;
    va_start(args, format);
    vdprintf(fd, format, args);
    va_end(args);
}

/* =======================================================
   Data Structure: doubly–linked list node.
   ======================================================= */
typedef struct s_node
{
    int             data;
    struct s_node   *next;
    struct s_node   *prev;
}   t_node;

/* =======================================================
   Helper function prototypes (see definitions below).
   ======================================================= */
int     ft_isdigit(int c);
int     ft_atoi(const char *str);
long    ft_atol_handle(const char *str, int *valid);

/* =======================================================
   Operation prototypes (printing the command as you go).
   ======================================================= */
void    swap(t_node **stack, char c);           // sa or sb
void    push_stack(t_node **src, t_node **dest, char c); // pa or pb
void    rotate(t_node **stack, char c);         // ra or rb
void    reverse_rotate(t_node **stack, char c);   // rra or rrb

void    swap_both(t_node **stack_a, t_node **stack_b);      // ss
void    rotate_both(t_node **stack_a, t_node **stack_b);    // rr
void    reverse_rotate_both(t_node **stack_a, t_node **stack_b); // rrr

/* =======================================================
   Utility functions.
   ======================================================= */
int     get_stack_size(t_node *stack);
int     get_min(t_node *stack);
int     get_max(t_node *stack);
int     is_sorted(t_node *stack);

/* =======================================================
   Input validation.
   ======================================================= */
int     ft_is_number(char *str);
int     ft_is_all_number(char **str);
int     ft_is_duplicated(char **str);
int     validate_input(char **str);

/* =======================================================
   Creation and cleanup.
   ======================================================= */
t_node  *create_node(char *data);
t_node  *create_stack_a(char **str);
void    cleanup_nodes(t_node **stack);
void    free_resource(t_node **stack_a, t_node **stack_b);

/* =======================================================
   Sorting routines for small sizes.
   ======================================================= */
void    sort_two(t_node **stack);
void    sort_three(t_node **stack);
void    sort_four(t_node **stack_a, t_node **stack_b);
void    sort_five(t_node **stack_a, t_node **stack_b);

/* =======================================================
   Optimized sorting routine for large input (using chunks).
   ======================================================= */
void    sort_large(t_node **stack_a, t_node **stack_b);

/* =======================================================
   Dispatcher: choose the right sort.
   ======================================================= */
void    sort_stack(t_node **stack_a, t_node **stack_b);

/* =======================================================
   Implementation
   ======================================================= */

/* ----- Basic Helpers ----- */
int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

/* A simple atoi that does not check overflow. */
int ft_atoi(const char *str)
{
    int sign = 1;
    int res = 0;
    while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str && ft_isdigit(*str))
    {
        res = res * 10 + (*str - '0');
        str++;
    }
    return (sign * res);
}

/* A simple atol_handle that sets valid=0 if not valid.
   (For simplicity, we assume no overflow in this demo.) */
long ft_atol_handle(const char *str, int *valid)
{
    long sign = 1;
    long res = 0;
    while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    if (!ft_isdigit(*str))
    {
        *valid = 0;
        return (0);
    }
    while (*str && ft_isdigit(*str))
    {
        res = res * 10 + (*str - '0');
        str++;
    }
    return (res * sign);
}

/* ----- Operations ----- */
void swap(t_node **stack, char c)
{
    t_node *first;
    t_node *second;

    if (!stack || !*stack || !((*stack)->next))
        return ;
    first = *stack;
    second = first->next;
    first->next = second->next;
    if (second->next)
        second->next->prev = first;
    second->next = first;
    second->prev = first->prev;  /* should be NULL */
    first->prev = second;
    *stack = second;
    if (c == 'a')
        ft_printf("sa\n");
    else
        ft_printf("sb\n");
}

void push_stack(t_node **src, t_node **dest, char c)
{
    t_node *tmp;
    if (!src || !*src)
        return ;
    tmp = *src;
    *src = tmp->next;
    if (*src)
        (*src)->prev = NULL;
    tmp->next = *dest;
    if (*dest)
        (*dest)->prev = tmp;
    *dest = tmp;
    tmp->prev = NULL;
    if (c == 'a')
        ft_printf("pa\n");
    else
        ft_printf("pb\n");
}

void rotate(t_node **stack, char c)
{
    t_node *tmp;
    t_node *last;
    if (!stack || !*stack || !((*stack)->next))
        return ;
    tmp = *stack;
    last = *stack;
    while (last->next)
        last = last->next;
    *stack = tmp->next;
    (*stack)->prev = NULL;
    tmp->next = NULL;
    tmp->prev = last;
    last->next = tmp;
    if (c == 'a')
        ft_printf("ra\n");
    else
        ft_printf("rb\n");
}

void reverse_rotate(t_node **stack, char c)
{
    t_node *tmp;
    t_node *last;
    if (!stack || !*stack || !((*stack)->next))
        return ;
    tmp = *stack;
    last = *stack;
    while (last->next)
        last = last->next;
    last->prev->next = NULL;
    last->prev = NULL;
    last->next = tmp;
    tmp->prev = last;
    *stack = last;
    if (c == 'a')
        ft_printf("rra\n");
    else
        ft_printf("rrb\n");
}

/* Combined operations */
void swap_both(t_node **stack_a, t_node **stack_b)
{
    /* We call individual swap functions then print combined command */
    swap(stack_a, 'a');
    swap(stack_b, 'b');
    ft_printf("ss\n");
}

void rotate_both(t_node **stack_a, t_node **stack_b)
{
    rotate(stack_a, 'a');
    rotate(stack_b, 'b');
    ft_printf("rr\n");
}

void reverse_rotate_both(t_node **stack_a, t_node **stack_b)
{
    reverse_rotate(stack_a, 'a');
    reverse_rotate(stack_b, 'b');
    ft_printf("rrr\n");
}

/* ----- Utility functions ----- */
int get_stack_size(t_node *stack)
{
    int size = 0;
    while (stack)
    {
        size++;
        stack = stack->next;
    }
    return size;
}

int get_min(t_node *stack)
{
    int min;
    if (!stack)
        return 0;
    min = stack->data;
    while (stack)
    {
        if (stack->data < min)
            min = stack->data;
        stack = stack->next;
    }
    return min;
}

int get_max(t_node *stack)
{
    int max;
    if (!stack)
        return 0;
    max = stack->data;
    while (stack)
    {
        if (stack->data > max)
            max = stack->data;
        stack = stack->next;
    }
    return max;
}

int is_sorted(t_node *stack)
{
    while (stack && stack->next)
    {
        if (stack->data > stack->next->data)
            return 0;
        stack = stack->next;
    }
    return 1;
}

/* ----- Input validation ----- */
int ft_is_number(char *str)
{
    int i = 0;
    if (!str || !str[0])
        return 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int ft_is_all_number(char **str)
{
    int i = 0;
    while (str[i])
    {
        if (!ft_is_number(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int ft_is_duplicated(char **str)
{
    int i, j;
    i = 0;
    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (ft_atoi(str[i]) == ft_atoi(str[j]))
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}

int validate_input(char **str)
{
    if (!ft_is_all_number(str))
    {
        ft_dprintf(2, "Error: Invalid Input\n");
        return 1;
    }
    if (ft_is_duplicated(str))
    {
        ft_dprintf(2, "Error: Duplicated Numbers\n");
        return 1;
    }
    return 0;
}

/* ----- Creation and Cleanup ----- */
t_node *create_node(char *data)
{
    t_node *node;
    int valid = 1;
    
    node = malloc(sizeof(t_node));
    if (!node)
        return NULL;
    node->data = (int)ft_atol_handle(data, &valid);
    node->next = NULL;
    node->prev = NULL;
    if (!valid)
    {
        free(node);
        return NULL;
    }
    return node;
}

t_node *create_stack_a(char **str)
{
    t_node *stack_a = NULL;
    t_node *tail = NULL;
    t_node *new_node;
    int i = 0;
    
    while (str[i])
    {
        new_node = create_node(str[i]);
        if (!new_node)
        {
            cleanup_nodes(&stack_a);
            return NULL;
        }
        if (!stack_a)
            stack_a = new_node;
        else
        {
            tail->next = new_node;
            new_node->prev = tail;
        }
        tail = new_node;
        i++;
    }
    return stack_a;
}

void cleanup_nodes(t_node **stack)
{
    t_node *tmp;
    while (*stack)
    {
        tmp = *stack;
        *stack = (*stack)->next;
        free(tmp);
    }
}

void free_resource(t_node **stack_a, t_node **stack_b)
{
    if (stack_a)
        cleanup_nodes(stack_a);
    if (stack_b)
        cleanup_nodes(stack_b);
}

/* ----- Sorting routines for small sizes ----- */
void sort_two(t_node **stack)
{
    if ((*stack)->data > (*stack)->next->data)
        swap(stack, 'a');
}

void sort_three(t_node **stack)
{
    int max = get_max(*stack);
    if ((*stack)->data == max)
    {
        rotate(stack, 'a');
        if (!is_sorted(*stack))
            swap(stack, 'a');
    }
    else if ((*stack)->next->data == max)
    {
        reverse_rotate(stack, 'a');
        if (!is_sorted(*stack))
            swap(stack, 'a');
    }
    else
    {
        if (!is_sorted(*stack))
            swap(stack, 'a');
    }
}

void sort_four(t_node **stack_a, t_node **stack_b)
{
    /* Push minimum element to B, sort three, then push back */
    int min = get_min(*stack_a);
    int size = get_stack_size(*stack_a);
    int pos = 0;
    t_node *tmp = *stack_a;
    while (tmp && tmp->data != min)
    {
        pos++;
        tmp = tmp->next;
    }
    /* Bring min to top */
    if (pos <= size / 2)
    {
        while (pos-- > 0)
            rotate(stack_a, 'a');
    }
    else
    {
        pos = size - pos;
        while (pos-- > 0)
            reverse_rotate(stack_a, 'a');
    }
    push_stack(stack_a, stack_b, 'b');
    sort_three(stack_a);
    push_stack(stack_b, stack_a, 'a');
}

void sort_five(t_node **stack_a, t_node **stack_b)
{
    /* Push two smallest to B, sort three, then push back */
    int i = 0;
    while (i < 2)
    {
        int min = get_min(*stack_a);
        int size = get_stack_size(*stack_a);
        int pos = 0;
        t_node *tmp = *stack_a;
        while (tmp && tmp->data != min)
        {
            pos++;
            tmp = tmp->next;
        }
        if (pos <= size / 2)
        {
            while (pos-- > 0)
                rotate(stack_a, 'a');
        }
        else
        {
            pos = size - pos;
            while (pos-- > 0)
                reverse_rotate(stack_a, 'a');
        }
        push_stack(stack_a, stack_b, 'b');
        i++;
    }
    sort_three(stack_a);
    push_stack(stack_b, stack_a, 'a');
    push_stack(stack_b, stack_a, 'a');
}

/* ----- Optimized sorting for large inputs ----- */

/*
    This implementation uses a chunk-based algorithm with best-candidate selection
    and combined rotations. It:
      1. Creates a sorted copy of stack A.
      2. Divides the sorted array into chunks.
      3. For each chunk, scans stack A to find the element (within the chunk)
         that requires the fewest rotations to bring to the top.
      4. Uses combined rotations (rr / rrr) when possible.
      5. Pushes the candidate to B. After pushing, if its sorted index is in the lower
         half of the chunk, rotates B.
      6. After all elements are in B, reassembles A by repeatedly moving the maximum
         from B back to A.
*/

/* Helper: Find index of value in sorted array */
static int find_index(int *sorted, int size, int value)
{
    int i = 0;
    while (i < size)
    {
        if (sorted[i] == value)
            return i;
        i++;
    }
    return -1;
}

/* Helper: Find the best candidate’s index in stack A that belongs to the current chunk.
   It returns the position (0-based from the top) that requires the fewest moves.
*/
static int get_best_candidate_index(t_node *stack, int *sorted, int total_size,
        int lower_bound, int upper_bound)
{
    int best_index = -1;
    int best_moves = -1;
    int index = 0;
    int stack_size = get_stack_size(stack);
    t_node *curr = stack;
    while (curr)
    {
        int sorted_idx = find_index(sorted, total_size, curr->data);
        if (sorted_idx >= lower_bound && sorted_idx <= upper_bound)
        {
            int moves = (index <= stack_size / 2) ? index : stack_size - index;
            if (best_index == -1 || moves < best_moves)
            {
                best_index = index;
                best_moves = moves;
            }
        }
        index++;
        curr = curr->next;
    }
    return best_index;
}

/* Helper: Bring the element at target_index to the top of the given stack.
   Uses combined rotations if a secondary stack is provided and the other stack
   also needs rotation. Here, we allow an optional second stack for combination.
   If second_stack is NULL, only rotate the first stack.
*/
static void bring_to_top(t_node **stack, t_node **second_stack, int target_index, char c, char c2)
{
    int size = get_stack_size(*stack);
    if (target_index <= size / 2)
    {
        while (target_index-- > 0)
        {
            /* If second_stack is provided and not empty, check if it also needs forward rotation.
               Here we combine if possible. */
            if (second_stack && *second_stack && get_stack_size(*second_stack) > 1)
            {
                /* For demonstration, we combine if both stacks are rotated forward.
                   (A more complex heuristic can be applied.) */
                rotate_both(stack, second_stack);
            }
            else
                rotate(stack, c);
        }
    }
    else
    {
        target_index = size - target_index;
        while (target_index-- > 0)
        {
            if (second_stack && *second_stack && get_stack_size(*second_stack) > 1)
            {
                reverse_rotate_both(stack, second_stack);
            }
            else
                reverse_rotate(stack, c);
        }
    }
}

void sort_large(t_node **stack_a, t_node **stack_b)
{
    int size, i;
    int *sorted;
    int chunk_count, chunk_size, current_chunk;
    int lower_bound, upper_bound;
    int best_index, median_index;
    
    /* 1. Build sorted copy of stack_a values */
    size = get_stack_size(*stack_a);
    sorted = malloc(sizeof(int) * size);
    if (!sorted)
        return;
    i = 0;
    {
        t_node *tmp = *stack_a;
        while (tmp)
        {
            sorted[i++] = tmp->data;
            tmp = tmp->next;
        }
    }
    qsort(sorted, size, sizeof(int), (int(*)(const void*,const void*)) compare_int);
    
    /* 2. Decide chunk count: for 500 numbers we use 11 chunks (tweak as needed) */
    chunk_count = (size <= 100 ? 5 : 11);
    chunk_size = size / chunk_count;
    current_chunk = 0;
    
    /* 3. Process stack_a until empty */
    while (get_stack_size(*stack_a) > 0)
    {
        lower_bound = current_chunk * chunk_size;
        upper_bound = (current_chunk == chunk_count - 1) ? (size - 1)
                        : ((current_chunk + 1) * chunk_size - 1);
        best_index = get_best_candidate_index(*stack_a, sorted, size, lower_bound, upper_bound);
        if (best_index == -1)
        {
            current_chunk++;
            continue;
        }
        /* Bring candidate to top of A. Try to combine rotation with B if possible. */
        bring_to_top(stack_a, stack_b, best_index, 'a', 'b');
        push_stack(stack_a, stack_b, 'b');
        /* After pushing, if the pushed element is in the lower half of the chunk,
           rotate B so that smaller numbers go deeper. */
        median_index = lower_bound + (chunk_size / 2);
        if (find_index(sorted, size, (*stack_b)->data) < median_index)
            rotate(stack_b, 'b');
    }
    
    /* 4. Reassemble A: push back from B to A in descending order.
       For each iteration, bring the maximum element in B to the top. */
    while (get_stack_size(*stack_b) > 0)
    {
        t_node *tmp = *stack_b;
        int pos = 0, size_b = get_stack_size(*stack_b);
        int max = get_max(*stack_b);
        while (tmp)
        {
            if (tmp->data == max)
                break;
            pos++;
            tmp = tmp->next;
        }
        bring_to_top(stack_b, NULL, pos, 'b', 0);
        push_stack(stack_b, stack_a, 'a');
    }
    free(sorted);
}

/* ----- Dispatcher ----- */
void sort_stack(t_node **stack_a, t_node **stack_b)
{
    int size = get_stack_size(*stack_a);
    if (size == 2)
        sort_two(stack_a);
    else if (size == 3)
        sort_three(stack_a);
    else if (size == 4)
        sort_four(stack_a, stack_b);
    else if (size == 5)
        sort_five(stack_a, stack_b);
    else
        sort_large(stack_a, stack_b);
}

/* ----- Main ----- */
int main(int argc, char **argv)
{
    t_node *stack_a = NULL;
    t_node *stack_b = NULL;
    
    if (argc < 2)
    {
        ft_dprintf(2, "Usage: %s <Numbers>\n", argv[0]);
        return 1;
    }
    /* Skip program name; validate the remaining arguments */
    if (validate_input(&argv[1]))
        return 1;
    
    stack_a = create_stack_a(&argv[1]);
    if (!stack_a)
    {
        ft_dprintf(2, "Error: Memory Allocation Failed\n");
        return 1;
    }
    if (is_sorted(stack_a))
    {
        free_resource(&stack_a, &stack_b);
        return 0;
    }
    sort_stack(&stack_a, &stack_b);
    free_resource(&stack_a, &stack_b);
    return 0;
}
