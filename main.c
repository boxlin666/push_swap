#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (0);
	parse_arguments(argc, argv, &stack_a);
	if (!stack_a || is_sorted(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	sort_stack(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}