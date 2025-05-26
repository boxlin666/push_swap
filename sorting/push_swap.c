/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:58:41 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 15:56:07 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"

int is_sorted(t_stack *stack)
{
    t_node *current;

    if (stack->size <= 1) // 空栈或只有一个元素，视为已排序
        return (1);
    current = stack->head;
    while (current && current->next)
    {
        if (current->value > current->next->value)
            return (0); // 当前值大于下一个值，未排序
        current = current->next;
    }
    return (1); // 遍历完成，栈已排序
}

void push_swap(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    if (is_sorted(stack_a))
        return;
    if (stack_a->size <= 3)
        sort_small(stack_a, operations);
    else if (stack_a->size <= 5)
        sort_medium(stack_a, stack_b, operations);
    else
        sort_large(stack_a, stack_b, operations);
}
