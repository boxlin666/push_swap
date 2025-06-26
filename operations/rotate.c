/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:38:12 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 14:31:07 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_ra(t_stack *stack_a, t_operation **operations)
{
	t_node	*first;

	if (stack_a->size < 2)
		return ;
	first = stack_a->head;
	stack_a->head = first->next;
	stack_a->head->prev = NULL;
	first->next = NULL;
	first->prev = stack_a->tail;
	stack_a->tail->next = first;
	stack_a->tail = first;
	*operations = add_operation(*operations, "ra");
}

void	do_rb(t_stack *stack_b, t_operation **operations)
{
	t_node	*first;

	if (stack_b->size < 2)
		return ;
	first = stack_b->head;
	stack_b->head = first->next;
	stack_b->head->prev = NULL;
	first->next = NULL;
	first->prev = stack_b->tail;
	stack_b->tail->next = first;
	stack_b->tail = first;
	*operations = add_operation(*operations, "rb");
}

void	do_rr(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
	do_ra(stack_a, operations);
	do_rb(stack_b, operations);
}
