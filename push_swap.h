#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h" // Assuming libft is in a subfolder

typedef struct s_node
{
	int				value;
	int				index; // Optional: useful for more complex algorithms
	struct s_node	*next;
}	t_node;

// --- Stack Operations ---
void	sa(t_node **stack_a, int print);
void	sb(t_node **stack_b, int print);
void	ss(t_node **stack_a, t_node **stack_b, int print);
void	pa(t_node **stack_a, t_node **stack_b, int print);
void	pb(t_node **stack_a, t_node **stack_b, int print);
void	ra(t_node **stack_a, int print);
void	rb(t_node **stack_b, int print);
void	rr(t_node **stack_a, t_node **stack_b, int print);
void	rra(t_node **stack_a, int print);
void	rrb(t_node **stack_b, int print);
void	rrr(t_node **stack_a, t_node **stack_b, int print);

// --- Parsing & Initialization ---
void	parse_arguments(int argc, char **argv, t_node **stack_a);
void	init_stack(t_node **stack, int value);
void	add_node_back(t_node **stack, t_node *new_node);

// --- Sorting Logic ---
void	sort_stack(t_node **stack_a, t_node **stack_b);
void	simple_sort(t_node **stack_a, t_node **stack_b);
void	sort_three(t_node **stack_a);

// --- Utility Functions ---
int		is_sorted(t_node *stack);
int		get_stack_size(t_node *stack);
t_node	*get_stack_bottom(t_node *stack);
t_node	*get_stack_before_bottom(t_node *stack);
int		find_min_value_pos(t_node *stack);
void	free_stack(t_node **stack);
void	error_exit(t_node **stack_a, t_node **stack_b);
long	ft_atol_check(const char *str, int *error_flag);

#endif