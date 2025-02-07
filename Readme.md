### OVERVIEW

The program *push_swap* sorts numbers using two stacks (A and B) and a set of allowed operations (swap, push, rotate, reverse-rotate and etc..). The code is organized into several modules:

1.  **Validations (validations.c):**\
    Checks that the input strings represent valid numbers and that no duplicates exist.

2.  **Creation (creations.c):**\
    Creates nodes for each number, builds the initial stack A (a doubly linked list), and produces a sorted copy of the numbers in an array.

3.  **Math & Quicksort (math_utils.c & sort_utils.c):**\
    Provide helper functions (like gcd, lcm) and sort the array using quicksort so that we know the correct order.

4.  **Stack Utilities (stack_utils.c):**\
    Provide functions to update positions, count elements, and perform the final rotation so that the smallest element is on top.

5.  **Operations (swap_operations.c & both_free.c):**\
    Implement basic moves (swap, push, rotate, reverse rotate) and some "double" operations (rotating both stacks at once).

6.  **Large-Set Sorting (sort_large.c & sort_large_utils.c):**\
    When the number of elements is greater than 3, the algorithm uses a "chunk" strategy to push most elements from A to B and then reinsert them in order using calculated rotations.

7.  **Main (main.c):**\
    Brings it all together: validates input, builds the stacks, decides which sorting routine to use, and finally cleans up.

In our example with 14 elements the program will use the "large sort" routine (since 14 > 3).

──────────────────────────────

### 1\. INPUT VALIDATION (validations.c)

#### **is_valid_number(char *str)**

-   **Purpose:**\
    To ensure that each input string is a valid integer.
-   **Step by Step:**
    1.  If the string begins with a '+' or '-', skip that character.
    2.  Then check every remaining character to see if it is a digit (using a function like `ft_isdigit`).
    3.  For example, `"10"` is checked as '1' and '0' (both digits).\
        Similarly, `"-2"` is accepted because the '-' is allowed and then '2' is a digit.
-   **Result:**\
    All 14 strings pass this check.

#### **check_duplicates(char **str)**

-   **Purpose:**\
    To ensure that there are no duplicate numbers.
-   **Step by Step:**
    1.  Convert the first string (say, `"10"`) to an integer (10) using a helper like `ft_atol_handle`.
    2.  Compare it with each subsequent number.
    3.  Continue for each element; for example, compare 10 with 3, 7, 1, etc.
-   **Result:**\
    In our example, all 14 numbers are unique.

#### **validate_input(char **str)**

-   **Purpose:**\
    To run both of the above validations.
-   **Step by Step:**
    1.  Loop through every string in the input.
    2.  For each, call `is_valid_number`.
    3.  After that, call `check_duplicates`.
-   **Result:**\
    Since all our strings are valid and there are no duplicates, validation passes.

──────────────────────────────

### 2\. STACK CREATION (creations.c)

#### **create_node(char *data)**

-   **Purpose:**\
    Create a new node (of type `t_node`) that will hold one number.
-   **Step by Step:**
    1.  Allocate memory for the node.
    2.  Convert the string to an integer using `ft_atol_handle`.\
        For example, for `"10"`, the node's `data` becomes **10**.
    3.  Set `next` and `prev` to `NULL`, and initialize `pos` to 0.
    4.  If conversion fails, free the node and return `NULL`.
-   **Result:**\
    A node is returned with the appropriate number stored.

#### **create_stack(char **str)**

-   **Purpose:**\
    Build the initial stack A (a doubly linked list) from the input strings.
-   **Step by Step:**
    1.  Initialize two pointers: `stack` (the head) and `tail` (the end) to `NULL`.
    2.  Loop through the array of 14 strings.\
        For each string, call `create_node`.
    3.  For the first string, set `stack` to the new node.\
        For subsequent nodes, link them by setting `tail->next = new_node` and `new_node->prev = tail`.
    4.  Update `tail` to be the new node.
-   **Result:**\
    You end up with a linked list of 14 nodes in the order of the input:

    css

    نسختحرير

    `[10] <-> [3] <-> [7] <-> [1] <-> [5] <-> [12] <-> [8] <-> [-2] <-> [4] <-> [0] <-> [15] <-> [-3] <-> [6] <-> [9]`

#### **create_sorted_array(t_node *stack)**

-   **Purpose:**\
    Create a copy of the numbers from the stack into an array and then sort that array.
-   **Step by Step:**
    1.  Use `get_stack_size(stack)` to determine the size (14).
    2.  Allocate an array of 14 integers.
    3.  Traverse the stack, copying each node's `data` into the array.\
        The unsorted array becomes:\
        `[10, 3, 7, 1, 5, 12, 8, -2, 4, 0, 15, -3, 6, 9]`
    4.  Call `ft_quicksort` (described later) on this array.
-   **Result:**\
    After sorting, the array might be:\
    `[-3, -2, 0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15]`\
    This sorted order will be used to determine "chunks" later.

──────────────────────────────

### 3\. MATH HELPERS & QUICKSORT (math_utils.c & sort_utils.c)

#### **gcd(int a, int b)**

-   **Purpose:**\
    Compute the greatest common divisor.
-   **Step by Step:**
    1.  While `b` is not zero, compute `t = a % b`, then set `a = b` and `b = t`.
    2.  Return `a` when the loop ends.
-   **Result:**\
    For example, gcd(14, 7) would yield 7.

#### **lcm(int a, int b)**

-   **Purpose:**\
    Compute the least common multiple.
-   **Step by Step:**
    1.  Use the formula: lcm = (a / gcd(a, b)) * b.
-   **Result:**\
    For our purposes, lcm is used in computing chunk counts.

#### **dynamic_chunk_count(int size)**

-   **Purpose:**\
    Determine how many chunks the algorithm should use based on the size of the input.
-   **Step by Step:**
    1.  If size ≤ 10, return 1.
    2.  Else if size ≤ 50, set a base (e.g., base = 2).
    3.  Compute lcm(size, base) and use its modulo with 3 as an offset.
    4.  Return `base + (lcm(size, base) % 3)`.
-   **Result:**\
    For 14 elements (14 ≤ 50), base = 2.\
    Suppose lcm(14, 2) = 14 (since gcd(14,2)=2 → (14/2)*2 = 14).\
    Then 14 % 3 = 2, so total chunks = 2 + 2 = **4**.\
    (You might sometimes see slight variations depending on implementation.)

#### **ft_swap(int *a, int *b)**

-   **Purpose:**\
    Swap two integer values.
-   **Step by Step:**
    1.  Save the value of *a in a temporary variable.
    2.  Set *a to *b and then *b to the temporary variable.
-   **Result:**\
    Swaps the two values.

#### **partition(int *arr, int low, int high)**

-   **Purpose:**\
    Partition an array segment around a pivot (for quicksort).
-   **Step by Step:**
    1.  Choose the pivot as the first element (arr[low]).
    2.  Initialize two indexes: i = low + 1 and j = high.
    3.  Increment i until you find a value greater than the pivot.
    4.  Decrement j until you find a value less than or equal to the pivot.
    5.  If i < j, swap arr[i] and arr[j]. Continue until i ≥ j.
    6.  Swap the pivot with arr[j] and return j as the pivot's final position.
-   **Result:**\
    The array is rearranged so that all values to the left of j are ≤ pivot and all values to the right are > pivot.

#### **ft_quicksort(int *arr, int low, int high)**

-   **Purpose:**\
    Sort the array using the quicksort algorithm.
-   **Step by Step:**
    1.  If low < high, partition the array and get the pivot index.
    2.  Recursively call ft_quicksort on the subarray before the pivot.
    3.  Recursively call ft_quicksort on the subarray after the pivot.
-   **Result:**\
    For our 14-element array, after all recursive calls, the array becomes:\
    `[-3, -2, 0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15]`.

──────────────────────────────

### 4\. STACK UTILITIES (stack_utils.c)

#### **get_stack_size(t_node *stack)**

-   **Purpose:**\
    Count how many nodes are in the stack.
-   **Step by Step:**
    1.  Initialize a counter to 0.
    2.  Traverse the list, incrementing the counter.
    3.  Return the count.
-   **Result:**\
    For our example, the function returns **14**.

#### **update_positions(t_node *stack)**

-   **Purpose:**\
    Update each node's `pos` field to match its index in the stack.
-   **Step by Step:**
    1.  Set pos = 0.
    2.  Traverse the stack and set each node's pos to the current count.
    3.  Increment the count for each node.
-   **Result:**\
    After calling this, the top node will have pos 0, the next pos 1, and so on.

#### **find_min_position(t_node *a)**

-   **Purpose:**\
    Find the position (index) of the node with the smallest value.
-   **Step by Step:**
    1.  Use `get_min(a)` to determine the smallest value.
    2.  Traverse the list until a node with that value is found.
    3.  Return its position.
-   **Result:**\
    For our sorted order, if --3 is the smallest, its position (in the current unsorted A) will be returned.

#### **optimize_rotations(t_node **stack, int rotations)**

-   **Purpose:**\
    Execute the required number of rotations or reverse rotations on a stack.
-   **Step by Step:**
    1.  If rotations is positive, call `rotate` repeatedly.
    2.  If rotations is negative, call `reverse_rotate` repeatedly.
-   **Result:**\
    The stack is rotated so that the desired element comes to the top.

#### **final_rotate(t_node **stack)**

-   **Purpose:**\
    After all elements have been reinserted into A, rotate A so that the smallest element is at the top.
-   **Step by Step:**
    1.  Call `find_min_position` to find the position of the smallest element.
    2.  Compute the number of rotations needed (if the position is in the first half, use rotate; if in the second half, use reverse_rotate).
    3.  Call `optimize_rotations` with that number.
-   **Result:**\
    The final sorted stack A has its smallest element at the top.

──────────────────────────────

### 5\. SWAP & ROTATION OPERATIONS (swap_operations.c & both_free.c)

#### **swap(t_node **s, char c, int both)**

-   **Purpose:**\
    Swap the first two nodes of a given stack.
-   **Step by Step:**
    1.  Check that the stack has at least two nodes.
    2.  Temporarily store the first node.
    3.  Set the head of the stack to the second node.
    4.  Link the first node after the second.
    5.  Update `prev` pointers as needed.
    6.  If `both` is false (i.e., not part of a simultaneous swap), print the command (for example, "sa" for stack A).
-   **Result:**\
    The top two nodes are exchanged.

#### **push_stack(t_node **src, t_node **dst, char c, int not_print)**

-   **Purpose:**\
    Move the top element from the source stack to the destination stack.
-   **Step by Step:**
    1.  Check that the source stack is not empty.
    2.  Remove the top node from `src`.
    3.  Insert that node at the front of `dst`.
    4.  Update the `prev` pointer of the former top of `dst` (if it exists).
    5.  If not suppressed by `not_print`, print the command (e.g., "pa" if pushing to A).
-   **Result:**\
    The top node is moved from one stack to the other.

#### **rotate(t_node **s, char c, int both)**

-   **Purpose:**\
    Move the first element of the stack to the bottom.
-   **Step by Step:**
    1.  Check that there are at least two nodes.
    2.  Save the first node in a temporary variable.
    3.  Advance the head pointer to the second node.
    4.  Traverse to the end of the stack.
    5.  Append the saved node at the end and update its `prev` pointer.
    6.  If not in a combined operation (`both` is false), print the command (e.g., "ra").
-   **Result:**\
    The stack is rotated upward by one position.

#### **reverse_rotate(t_node **s, char c, int both)**

-   **Purpose:**\
    Move the last element of the stack to the top.
-   **Step by Step:**
    1.  Check that there are at least two nodes.
    2.  Traverse to the last node.
    3.  Remove it from its current position.
    4.  Insert it at the beginning of the stack.
    5.  Update `prev` pointers accordingly.
    6.  Print the command if needed.
-   **Result:**\
    The stack is rotated downward by one position.

#### **rotate_both(t_node **a, t_node **b, int both)**

-   **Purpose:**\
    Simultaneously rotate both stacks A and B.
-   **Step by Step:**
    1.  Ensure that both stacks have at least two nodes.
    2.  Call `rotate` on A and B.
    3.  If not in a "both" operation (flag not set), print "rr".
-   **Result:**\
    Both stacks are rotated upward at the same time.

#### **reverse_rotate_both(t_node **a, t_node **b, int both)**

-   **Purpose:**\
    Simultaneously reverse rotate both stacks.
-   **Step by Step:**
    1.  Ensure that both stacks have at least two nodes.
    2.  Call `reverse_rotate` on A and B.
    3.  Print "rrr" if the flag is not set.
-   **Result:**\
    Both stacks are reverse rotated at the same time.

#### **swap_both(t_node **stack_a, t_node **stack_b, int both)**

-   **Purpose:**\
    Swap the first two elements of both stacks simultaneously.
-   **Step by Step:**
    1.  Call `swap` on stack A and then on stack B.
    2.  If the flag is false, print "ss".
-   **Result:**\
    Both stacks have their first two elements exchanged.

──────────────────────────────

### 6\. LARGE SET SORTING (sort_large.c & sort_large_utils.c)

Since 14 > 3, the program will use the large sort routine.

#### **sort_large(t_node **a, t_node **b)**

-   **Purpose:**\
    Sort a large stack (more than 3 elements) using a two-phase process:\
    (1) Move most elements from A to B in "chunks" and sort the 3 remaining in A;\
    (2) Reinsert elements from B back into A in the correct order.
-   **Step by Step:**
    1.  **Create Sorted Array:**
        -   Call `create_sorted_array(*a)` to obtain a sorted array of 14 elements.\
            (For our example, the sorted array is:\
            `[-3, -2, 0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15]`)
    2.  **Push Chunks:**
        -   Call `push_chunks(a, b, sorted, size)`.
        -   Inside `push_chunks`:\
            a. Initialize a `t_chunk` structure with:
            -   `size = 14`
            -   `total = dynamic_chunk_count(14)` → for 14 elements (since 14 ≤ 50), base = 2.\
                Suppose lcm(14, 2) = 14 and 14 % 3 = 2, then total chunks = 2 + 2 = 4.
            -   `chunk_size = size / total` = 14 / 4 = 3 (integer division)\
                (If less than 1, it would be set to 1, but here it is 3.)
            -   `current = 1` (starting with the first chunk)
            -   `sorted` points to the sorted array. b. While the size of stack A is greater than 3, do:
            -   Update positions on A (so each node's pos is updated).
            -   Find the index of the top element in the sorted array.\
                For example, if the top of A is **10**, its index in the sorted array is 11.
            -   Call `move_from_a_to_b(a, b, index, &chunk)`.
            -   **Inside move_from_a_to_b:**\
                - Check if the element's index is less than `chunk->current * chunk->chunk_size`.\
                For chunk 1, the threshold is 1×3 = 3.\
                Since 11 is not less than 3, the element is not in the first chunk; therefore,\
                it rotates stack A.
                -   If the element were in the correct range (for example, if the top were **-3**, index 0),\
                    then it would be pushed onto B.\
                    In addition, if `chunk->chunk_size > 1`, it checks a threshold value in the sorted array\
                    and may call `rotate(b, 'b', 0)` after pushing.
            -   After each push, if stack B's size becomes equal to `chunk->current * chunk->chunk_size`\
                and if there are more chunks left, increment `chunk->current`.\
                c. The loop stops when A has exactly 3 nodes.
    3.  **Sort the Remaining Three in A:**
        -   Call `sort_three(a)` to sort the last 3 nodes.
    4.  **Reinsert Nodes from B:**
        -   While stack B is not empty, repeat:\
            a. Update positions on both A and B.\
            b. Call `calculate_move(a, b, &ca, &cb)` to determine the best move.\
            - This function scans B and, for each node, computes how many rotations (for A and B)\
            would be needed to insert it into the correct position in A.\
            It uses `get_target_position` to know where in A the number fits.\
            - It selects the node (and its associated rotations) with the smallest "cost" (sum of\
            absolute rotations).\
            c. Call `execute_rotations(a, b, ca, cb)` to perform simultaneous rotations (if possible)\
            and then individual rotations so that the chosen node from B is aligned for insertion. d. Call `push_stack(b, a, 'a', 0)` to push that node into A.
    5.  **Final Rotation:**
        -   Once B is empty, call `final_rotate(a)` to bring the smallest element to the top of A.
    6.  **Cleanup:**
        -   Free the sorted array.
-   **Result:**\
    At the end of `sort_large`, all 14 elements are in stack A in ascending order.

#### **calculate_move(t_node **a, t_node **b, int *ca, int *cb)**

-   **Purpose:**\
    Determine which element in stack B should be moved next and how many rotations are needed.
-   **Step by Step:**
    1.  Update positions in both A and B.
    2.  If B is empty, set both move counters to 0 and return.
    3.  Initialize a local structure (`t_move`) that will keep:
        -   `sizes[0]` = size of A, `sizes[1]` = size of B.
    4.  For the first node in B, call `initialize_best` to record its target position in A (using `get_target_position`) and its own position.
    5.  For each subsequent node in B, call `update_best` to compute its "cost" (using the adjusted positions) and update the best move if the cost is lower.
    6.  Finally, assign the best move's rotation counts to *ca and *cb.
-   **Result:**\
    The function outputs the minimal number of rotations needed on A and B for the optimal candidate.

#### **execute_rotations(t_node **a, t_node **b, int ca, int cb)**

-   **Purpose:**\
    Execute the rotations on A and B based on the values computed by `calculate_move`.
-   **Step by Step:**
    1.  Call `execute_both_rotations(a, b, &ca, &cb)` to perform simultaneous rotations if both counters are of the same sign.
    2.  Then, while there are remaining rotations needed for A (if ca ≠ 0), perform them individually by calling `rotate` or `reverse_rotate`.
    3.  Do the same for B.
-   **Result:**\
    Both stacks are rotated so that the optimal candidate node in B is aligned with its target position in A.

──────────────────────────────

### 7\. MAIN FUNCTION (main.c)

#### **main(int argc, char **argv)**

-   **Purpose:**\
    The entry point of the program.
-   **Step by Step:**
    1.  Check that at least one argument (besides the program name) is provided.
    2.  Call `validate_input(argv + 1)` to ensure the input is correct.
    3.  Create stack A from the input by calling `create_stack(argv + 1)`.
    4.  If creation fails or the number of nodes does not match the expected count (14 in our case), free resources and exit.
    5.  If the stack is not already sorted (using `is_sorted`), call `sort_stack(&stack_a, &stack_b)`.\
        -- In our example, 14 is not 2 or 3, so it calls `sort_large`.
    6.  After sorting, free all resources (both stacks) by calling `free_resource(&stack_a, &stack_b)`.
    7.  Return 0 to indicate success.
-   **Result:**\
    The program prints the sorting operations (if in push_swap mode) and finishes with a sorted stack A.

──────────────────────────────

### SUMMARY OF THE EXAMPLE (14 ELEMENTS)

1.  **Input:**\
    The program receives 14 strings:\
    `[ "10", "3", "7", "1", "5", "12", "8", "-2", "4", "0", "15", "-3", "6", "9" ]`

2.  **Validation:**\
    Each string is checked for numeric validity and duplicate values. All pass.

3.  **Stack Creation:**\
    A doubly linked list (stack A) is built with nodes holding the values in the order given.\
    Initially:\
    A = [10] → [3] → [7] → [1] → [5] → [12] → [8] → [-2] → [4] → [0] → [15] → [-3] → [6] → [9]

4.  **Sorted Array & Quicksort:**\
    An array is built from the stack:\
    `[10, 3, 7, 1, 5, 12, 8, -2, 4, 0, 15, -3, 6, 9]`\
    After quicksort, it becomes:\
    `[-3, -2, 0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15]`

5.  **Chunk Setup:**\
    Using `dynamic_chunk_count`, the program determines (for example) that there will be 4 chunks.\
    Each chunk has a size of 3 (14/4 = 3, integer division).\
    The first chunk corresponds to the 3 smallest values (`[-3, -2, 0]`), the second chunk the next 3 (`[1, 3, 4]`), etc.

6.  **Push Chunks:**\
    The program enters a loop where it pushes nodes from A to B based on whether the node's value falls in the current chunk range.\
    -- For instance, if the top of A is 10 (whose sorted index is 11), and if the current chunk is 1 (values with indices < 3), then 10 is not in chunk 1; so the program rotates A.\
    -- When an element from A is in the current chunk (for example, if the top were -3), it is pushed to B. -- After enough elements are pushed so that B's size equals the chunk threshold (3 for chunk 1), the chunk counter is incremented. -- This continues until A is reduced to 3 nodes.

7.  **Sort Three:**\
    Once only 3 nodes remain in A, `sort_three` is called to arrange them in order.

8.  **Reinsertion from B:**\
    While B is not empty, the program:\
    -- Calculates for each node in B how many rotations are needed on both stacks to insert it into A in the right position.\
    -- Chooses the node with the lowest "cost."\
    -- Rotates A and B accordingly and then pushes the node from B back to A. -- This is done repeatedly until B is empty.

9.  **Final Rotation:**\
    Finally, `final_rotate` rotates A so that the smallest value (--3) ends up at the top.

10. **Result:**\
    At the end, stack A is completely sorted in ascending order:\
    `[-3, -2, 0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15]`

11. **Cleanup:**\
    All allocated memory (nodes and the sorted array) is freed, and the program terminates.

──────────────────────────────

### CONCLUSION

This explanation has covered every function in the program---from validating the input, creating the initial stack, building a sorted array using quicksort, calculating the "chunks" to determine which nodes to push to stack B, performing rotations and calculating the optimal move to reinsert nodes, and finally adjusting the sorted stack. By following these detailed steps with the example of 14 elements, you can see how each part of the code contributes to sorting the numbers.

If you study this explanation alongside the code, you should gain a thorough understanding of the complete process, how variables and data structures change over time, and how the operations work together to achieve the final sorted output.