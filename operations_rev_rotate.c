#include "push_swap.h"

static void	reverse_rotate(t_node **stack)
{
	t_node	*last;
	t_node	*before_last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	last = get_stack_bottom(*stack);
	before_last = get_stack_before_bottom(*stack);
	before_last->next = NULL;
	last->next = *stack;
	*stack = last;
}

void	rra(t_node **stack_a, int print)
{
	reverse_rotate(stack_a);
	if (print)
		ft_putendl_fd("rra", 1);
}

void	rrb(t_node **stack_b, int print)
{
	reverse_rotate(stack_b);
	if (print)
		ft_putendl_fd("rrb", 1);
}

void	rrr(t_node **stack_a, t_node **stack_b, int print)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	if (print)
		ft_putendl_fd("rrr", 1);
}