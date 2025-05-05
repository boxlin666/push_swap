#include "push_swap.h"

// Sorts only 3 elements in stack A
void	sort_three(t_node **stack_a)
{
	int	a;
	int	b;
	int	c;

	if (is_sorted(*stack_a))
		return ;
	a = (*stack_a)->value;
	b = (*stack_a)->next->value;
	c = (*stack_a)->next->next->value;
	if (a > b && b < c && a < c) // Case: 2 1 3 -> sa
		sa(stack_a, 1);
	else if (a < b && b > c && a < c) // Case: 1 3 2 -> rra, sa OR sa, ra
	{
		rra(stack_a, 1);
		sa(stack_a, 1);
	}
	else if (a > b && b > c) // Case: 3 2 1 -> sa, rra
	{
		sa(stack_a, 1);
		rra(stack_a, 1);
	}
	else if (a > b && b < c && a > c) // Case: 3 1 2 -> ra
		ra(stack_a, 1);
	else if (a < b && b > c && a > c) // Case: 2 3 1 -> rra
		rra(stack_a, 1);
}

// Basic, inefficient sorting algorithm: find smallest, rotate to top, push to B
void	simple_sort(t_node **stack_a, t_node **stack_b)
{
	int	size_a;
	int	min_pos;
	int	i;

	size_a = get_stack_size(*stack_a);
	while (size_a > 3 && !is_sorted(*stack_a))
	{
		min_pos = find_min_value_pos(*stack_a);
		if (min_pos <= size_a / 2)
		{
			i = 0;
			while (i < min_pos)
			{
				ra(stack_a, 1);
				i++;
			}
		}
		else
		{
			i = 0;
			while (i < size_a - min_pos)
			{
				rra(stack_a, 1);
				i++;
			}
		}
		pb(stack_a, stack_b, 1);
		size_a--;
	}
	if (size_a == 3)
		sort_three(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b, 1);
}

// Main sorting dispatcher
void	sort_stack(t_node **stack_a, t_node **stack_b)
{
	int	size;

	size = get_stack_size(*stack_a);
	if (size == 2)
		sa(stack_a, 1);
	else if (size == 3)
		sort_three(stack_a);
	else
		simple_sort(stack_a, stack_b); // Use the basic sort for > 3
}