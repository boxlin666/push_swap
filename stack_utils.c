#include "push_swap.h"

int	get_stack_size(t_node *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

int	is_sorted(t_node *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

t_node	*get_stack_bottom(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

t_node	*get_stack_before_bottom(t_node *stack)
{
	if (!stack || !stack->next)
		return (NULL);
	while (stack->next->next)
		stack = stack->next;
	return (stack);
}

void	free_stack(t_node **stack)
{
	t_node	*current;
	t_node	*temp;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	*stack = NULL;
}

void	error_exit(t_node **stack_a, t_node **stack_b)
{
	free_stack(stack_a);
	free_stack(stack_b);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	find_min_value_pos(t_node *stack)
{
	int		min_val;
	int		min_pos;
	int		current_pos;
	t_node	*current;

	if (!stack)
		return (-1);
	min_val = stack->value;
	min_pos = 0;
	current_pos = 0;
	current = stack;
	while (current)
	{
		if (current->value < min_val)
		{
			min_val = current->value;
			min_pos = current_pos;
		}
		current = current->next;
		current_pos++;
	}
	return (min_pos);
}
