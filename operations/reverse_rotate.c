/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:38:34 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 12:11:24 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void do_rra(t_stack *stack_a, t_operation **operations)
{
    t_node *last;

    if (stack_a->size < 2)
        return;
    last = stack_a->tail;
    stack_a->tail = last->prev;
    stack_a->tail->next = NULL;
    last->prev = NULL;
    last->next = stack_a->head;
    stack_a->head->prev = last;
    stack_a->head = last;
    *operations = add_operation(*operations, "rra");
}

void do_rrb(t_stack *stack_b, t_operation **operations)
{
    t_node *last;

    if (stack_b->size < 2)
        return;
    last = stack_b->tail;
    stack_b->tail = last->prev;
    stack_b->tail->next = NULL;
    last->prev = NULL;
    last->next = stack_b->head;
    stack_b->head->prev = last;
    stack_b->head = last;
    *operations = add_operation(*operations, "rrb");
}

void do_rrr(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    do_rra(stack_a, operations);
    do_rrb(stack_b, operations);
}
