/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:38:12 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 13:52:19 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"

void do_ra(t_stack *stack_a, t_operation **operations)
{
    t_node *first;

    if (stack_a->size < 2) // 栈 a 元素少于 2 个，无需操作
        return;
    first = stack_a->head;
    stack_a->head = first->next; // 新栈顶是第二个元素
    stack_a->head->prev = NULL;
    first->next = NULL;
    first->prev = stack_a->tail; // 原栈顶连接到原栈底
    stack_a->tail->next = first;
    stack_a->tail = first; // 更新栈底为原栈顶
    *operations = add_operation(*operations, "ra"); // 记录操作（如果存储操作）
}

void do_rb(t_stack *stack_b, t_operation **operations)
{
    t_node *first;

    if (stack_b->size < 2) // 栈 b 元素少于 2 个，无需操作
        return;
    first = stack_b->head;
    stack_b->head = first->next; // 新栈顶是第二个元素
    stack_b->head->prev = NULL;
    first->next = NULL;
    first->prev = stack_b->tail; // 原栈顶连接到原栈底
    stack_b->tail->next = first;
    stack_b->tail = first; // 更新栈底为原栈顶
    *operations = add_operation(*operations, "rb"); // 记录操作（如果存储操作）
}

void do_rr(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    do_ra(stack_a, operations);
    do_rb(stack_b, operations);
}