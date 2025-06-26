/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:54:53 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 16:55:31 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_index(t_stack *stack_a)
{
	t_node	*p;
	int		min_num;
	int		index;
	int		min_index;

	p = stack_a->head;
	min_num = p->value;
	index = 0;
	min_index = 0;
	while (p != NULL)
	{
		if (p->value < min_num)
		{
			min_num = p->value;
			min_index = index;
		}
		p = p->next;
		index++;
	}
	return (min_index);
}

void	rotate_to_position(t_stack *stack, int min_index,
		t_operation **operations)
{
	int	size;
	int	forward_steps;
	int	backward_steps;

	if (stack->size == 0 || min_index == 0)
		return ;
	size = stack->size;
	forward_steps = min_index;
	backward_steps = size - min_index;
	if (forward_steps <= backward_steps)
	{
		while (forward_steps--)
			do_ra(stack, operations);
	}
	else
	{
		while (backward_steps--)
			do_rra(stack, operations);
	}
}

void	sort_medium(t_stack *stack_a, t_stack *stack_b,
		t_operation **operations)
{
	int	min_index;

	while (stack_a->size > 3)
	{
		min_index = get_min_index(stack_a);
		rotate_to_position(stack_a, min_index, operations);
		do_pb(stack_a, stack_b, operations);
	}
	sort_small(stack_a, operations);
	while (stack_b->size > 0)
	{
		do_pa(stack_a, stack_b, operations);
	}
}
