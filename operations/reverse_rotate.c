/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:38:34 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 13:50:48 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"

void do_rra(t_stack *stack_a, t_operation **operations)
{
    t_node *last;

    if (stack_a->size < 2) // 栈 a 元素少于 2 个，无需操作
        return;
    last = stack_a->tail;
    stack_a->tail = last->prev; // 新栈底是倒数第二个元素
    stack_a->tail->next = NULL;
    last->prev = NULL;
    last->next = stack_a->head; // 原栈底连接到原栈顶
    stack_a->head->prev = last;
    stack_a->head = last; // 更新栈顶为原栈底
    *operations = add_operation(*operations, "rra"); // 记录操作（如果存储操作）
}

void do_rrb(t_stack *stack_b, t_operation **operations)
{
    t_node *last;

    if (stack_b->size < 2) // 栈 b 元素少于 2 个，无需操作
        return;
    last = stack_b->tail;
    stack_b->tail = last->prev; // 新栈底是倒数第二个元素
    stack_b->tail->next = NULL;
    last->prev = NULL;
    last->next = stack_b->head; // 原栈底连接到原栈顶
    stack_b->head->prev = last;
    stack_b->head = last; // 更新栈顶为原栈底
    *operations = add_operation(*operations, "rrb"); // 记录操作（如果存储操作）
}

void do_rrr(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    do_rra(stack_a, operations);
    do_rrb(stack_b, operations);
}