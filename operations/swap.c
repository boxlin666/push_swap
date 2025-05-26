/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:34:17 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 15:16:25 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"

void do_sa(t_stack *stack_a, t_operation **operations)
{
    t_node *first;
    t_node *second;

    if (stack_a->size < 2) // 栈 a 元素少于 2 个，无需操作
        return;
    first = stack_a->head;
    second = stack_a->head->next;
    // 交换指针
    first->next = second->next;
    if (second->next)
        second->next->prev = first;
    else
        stack_a->tail = first; // 更新尾指针，如果 second 是最后一个节点
    second->next = first;
    second->prev = NULL;
    first->prev = second;
    stack_a->head = second;
    *operations = add_operation(*operations, "sa"); // 记录操作（如果存储操作）
}

void do_sb(t_stack *stack_b, t_operation **operations)
{
    t_node *first;
    t_node *second;

    if (stack_b->size < 2) // 栈 b 元素少于 2 个，无需操作
        return;
    first = stack_b->head;
    second = stack_b->head->next;
    // 交换指针
    first->next = second->next;
    if (second->next)
        second->next->prev = first;
    else
        stack_b->tail = first; // 更新尾指针，如果 second 是最后一个节点
    second->next = first;
    second->prev = NULL;
    first->prev = second;
    stack_b->head = second;
    *operations = add_operation(*operations, "sb"); // 记录操作（如果存储操作）
}

void do_ss(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    do_sa(stack_a, operations);
    do_sb(stack_b, operations);
}