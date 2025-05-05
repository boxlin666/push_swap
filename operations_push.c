#include "push_swap.h"

static void	push(t_node **stack_from, t_node **stack_to)
{
	t_node	*node_to_push;

	if (!stack_from || !*stack_from)
		return ;
	node_to_push = *stack_from;
	*stack_from = (*stack_from)->next;
	node_to_push->next = *stack_to;
	*stack_to = node_to_push;
}

void	pa(t_node **stack_a, t_node **stack_b, int print)
{
	push(stack_b, stack_a);
	if (print)
		ft_putendl_fd("pa", 1);
}

void	pb(t_node **stack_a, t_node **stack_b, int print)
{
	push(stack_a, stack_b);
	if (print)
		ft_putendl_fd("pb", 1);
}
