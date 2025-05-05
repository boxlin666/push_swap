#include "push_swap.h"

static void	swap(t_node **stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	sa(t_node **stack_a, int print)
{
	swap(stack_a);
	if (print)
		ft_putendl_fd("sa", 1);
}

void	sb(t_node **stack_b, int print)
{
	swap(stack_b);
	if (print)
		ft_putendl_fd("sb", 1);
}

void	ss(t_node **stack_a, t_node **stack_b, int print)
{
	swap(stack_a);
	swap(stack_b);
	if (print)
		ft_putendl_fd("ss", 1);
}
