/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:07:15 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

int	get_chunk_count(int size)
{
	if (size <= 100)
		return (2);
	else
		return (4);
}

void	sort_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
	int	num_chunks;
	int	chunk_size;
	int	max_size;
	int	i;
	int	head_value;

	num_chunks = get_chunk_count(stack_a->size);
	chunk_size = stack_a->size / num_chunks;
	max_size = stack_a->size;
	i = 0;
	while (i < num_chunks)
	{
		if (i != num_chunks - 1)
			slice_stack(stack_a, stack_b, operations, i * chunk_size, (i + 1)
				* chunk_size);
		else
			slice_stack(stack_a, stack_b, operations, i * chunk_size, max_size);
		i++;
	}
	while (stack_b->size > 0)
	{
		if (stack_a->size == 0)
			do_pa(stack_a, stack_b, operations);
		else if (stack_a->size == 1)
		{
			do_pa(stack_a, stack_b, operations);
			if (stack_a->head->value > stack_a->tail->value)
				do_sa(stack_a, operations);
		}
		else
			move_next_element(stack_a, stack_b, operations);
	}
	head_value = stack_a->head->value;
	if (head_value < stack_a->size / 2)
	{
		while (head_value--)
			do_rra(stack_a, operations);
	}
	else
	{
		head_value = stack_a->size - head_value;
		while (head_value--)
			do_ra(stack_a, operations);
	}
}
