/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:58:41 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 11:32:35 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (stack->size <= 1)
		return (1);
	current = stack->head;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

void	push_swap(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
	if (is_sorted(stack_a))
		return ;
	if (stack_a->size <= 3)
		sort_small(stack_a, operations);
	else if (stack_a->size <= 5)
		sort_medium(stack_a, stack_b, operations);
	else
		sort_large(stack_a, stack_b, operations);
}
