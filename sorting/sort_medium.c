/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:54:53 by helin             #+#    #+#             */
/*   Updated: 2025/05/26 17:05:18 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"

int get_min_index(t_stack *stack_a)
{
    t_node *p = stack_a->head;
    int min_num = p->value; 
    int index = 0;  
    int min_index = 0;   

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
    return min_index; 
}

void rotate_to_position(t_stack *stack, int min_index, t_operation **operations)
{
    if (stack->size == 0 || min_index == 0)
        return;
    int size = stack->size;
    int forward_steps = min_index;
    int backward_steps = size - min_index;
    if (forward_steps <= backward_steps)
    {
        for (int i = 0; i < forward_steps; i++)
            do_ra(stack, operations);
    }
    else
    {
        for (int i = 0; i < backward_steps; i++)
            do_rra(stack, operations);
    }
}

void sort_medium(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    while (stack_a->size > 3){
        int min_index = get_min_index(stack_a);
        rotate_to_position(stack_a, min_index, operations); // 旋转到合适位置
        do_pb(stack_a, stack_b, operations);
    }
    sort_small(stack_a, operations); // 对 stack_a 剩余 3 个数字排序
    while (stack_b->size > 0) // 插入回 stack_a
    {
        do_pa(stack_a, stack_b, operations); // 推回 stack_a
    }
}