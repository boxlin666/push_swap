/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:31:08 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 12:11:17 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_pa(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
	t_node	*temp;

	if (stack_b->size == 0)
		return ;
	temp = stack_b->head;
	stack_b->head = stack_b->head->next;
	if (stack_b->head)
		stack_b->head->prev = NULL;
	else
		stack_b->tail = NULL;
	stack_b->size--;
	temp->next = stack_a->head;
	temp->prev = NULL;
	if (stack_a->head)
		stack_a->head->prev = temp;
	else
		stack_a->tail = temp;
	stack_a->head = temp;
	stack_a->size++;
	*operations = add_operation(*operations, "pa");
}

void	do_pb(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
	t_node *temp;

	if (stack_a->size == 0)
		return ;
	temp = stack_a->head;
	stack_a->head = stack_a->head->next;
	if (stack_a->head)
		stack_a->head->prev = NULL;
	else
		stack_a->tail = NULL;
	stack_a->size--;
	temp->next = stack_b->head;
	temp->prev = NULL;
	if (stack_b->head)
		stack_b->head->prev = temp;
	else
		stack_b->tail = temp;
	stack_b->head = temp;
	stack_b->size++;
	*operations = add_operation(*operations, "pb");
}