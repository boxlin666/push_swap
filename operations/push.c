/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:31:08 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 13:31:27 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"

void do_pa(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    t_node *temp;

    if (stack_b->size == 0) // 栈 b 为空，无需操作
        return;
    temp = stack_b->head; // 取栈 b 的栈顶节点
    stack_b->head = stack_b->head->next; // 更新栈 b 的栈顶
    if (stack_b->head)
        stack_b->head->prev = NULL;
    else
        stack_b->tail = NULL; // 栈 b 为空时更新尾指针
    stack_b->size--;
    temp->next = stack_a->head; // 插入到栈 a 的栈顶
    temp->prev = NULL;
    if (stack_a->head)
        stack_a->head->prev = temp;
    else
        stack_a->tail = temp; // 栈 a 为空时更新尾指针
    stack_a->head = temp;
    stack_a->size++;
    *operations = add_operation(*operations, "pa"); // 记录操作（如果存储操作）
}

void do_pb(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    t_node *temp;

    if (stack_a->size == 0) // 栈 a 为空，无需操作
        return;
    temp = stack_a->head; // 取栈 a 的栈顶节点
    stack_a->head = stack_a->head->next; // 更新栈 a 的栈顶
    if (stack_a->head)
        stack_a->head->prev = NULL;
    else
        stack_a->tail = NULL; // 栈 a 为空时更新尾指针
    stack_a->size--;
    temp->next = stack_b->head; // 插入到栈 b 的栈顶
    temp->prev = NULL;
    if (stack_b->head)
        stack_b->head->prev = temp;
    else
        stack_b->tail = temp; // 栈 b 为空时更新尾指针
    stack_b->head = temp;
    stack_b->size++;
    *operations = add_operation(*operations, "pb"); // 记录操作（如果存储操作）
}