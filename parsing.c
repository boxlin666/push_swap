#include "push_swap.h"

// Basic atoi with overflow/underflow check for long
long	ft_atol_check(const char *str, int *error_flag)
{
	long	res = 0;
	int		sign = 1;
	int		i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		*error_flag = 1;
	while (ft_isdigit(str[i]))
	{
		if (res > (LONG_MAX - (str[i] - '0')) / 10 && sign == 1)
			*error_flag = 1;
		if (sign == -1 && (-res < (LONG_MIN + (str[i] - '0')) / 10))
			*error_flag = 1;
		res = res * 10 + (str[i] - '0');
		i++;
	}
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) // Check trailing spaces
		i++;
	if (str[i] != '\0') // Check for non-digit characters after number
		*error_flag = 1;
	return (res * sign);
}


static void	check_duplicates(t_node *stack)
{
	t_node	*current;
	t_node	*runner;

	current = stack;
	while (current)
	{
		runner = current->next;
		while (runner)
		{
			if (current->value == runner->value)
				error_exit(&stack, NULL);
			runner = runner->next;
		}
		current = current->next;
	}
}

void	add_node_back(t_node **stack, t_node *new_node)
{
	t_node	*temp;

	if (!stack || !new_node)
		return ;
	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	temp = get_stack_bottom(*stack);
	temp->next = new_node;
}


void	init_stack(t_node **stack, int value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		error_exit(stack, NULL);
	new_node->value = value;
	new_node->index = 0; // Initialize index if needed later
	new_node->next = NULL;
	add_node_back(stack, new_node);
}

void	parse_arguments(int argc, char **argv, t_node **stack_a)
{
	int		i;
	long	num;
	int		error_flag;

	i = 1;
	error_flag = 0;
	while (i < argc)
	{
		// Basic check: allow only digits and a leading sign
		int j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+') j++;
		if (argv[i][j] == '\0') error_flag = 1; // Only sign is not allowed
		while(argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				error_flag = 1;
				break;
			}
			j++;
		}
        if (error_flag) break;

		num = ft_atol_check(argv[i], &error_flag);
		if (error_flag || num > INT_MAX || num < INT_MIN)
			break;
		init_stack(stack_a, (int)num);
		i++;
	}
	if (error_flag)
		error_exit(stack_a, NULL);
	check_duplicates(*stack_a);
}
