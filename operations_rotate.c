#include "push_swap.h"

static void	rotate(t_node **stack)
{
	t_node	*first;
	t_node	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = get_stack_bottom(*stack);
	*stack = first->next;
	first->next = NULL;
	last->next = first;
}

void	ra(t_node **stack_a, int print)
{
	rotate(stack_a);
	if (print)
		ft_putendl_fd("ra", 1);
}

void	rb(t_node **stack_b, int print)
{
	rotate(stack_b);
	if (print)
		ft_putendl_fd("rb", 1);
}

void	rr(t_node **stack_a, t_node **stack_b, int print)
{
	rotate(stack_a);
	rotate(stack_b);
	if (print)
		ft_putendl_fd("rr", 1);
}