/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/02 17:17:51 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <stdlib.h>
#include <limits.h>

int get_chunk_count(int size)
{
    if (size <= 100)
        return 5;
    else
        return size / 50 + 5;
}

int find_ra_next(t_stack *stack, int min_val, int max_val)
{
    if (stack->size == 0)
        return 0;
    t_node *current = stack->head;
    int min_step = stack->size;
    int step = 0;
    while (current)
    {
        if (current->value >= min_val && current->value < max_val)
            break;
        current = current->next;
        step++;
    }
    if (min_step > step)
        min_step = step;
    return min_step;
}

int find_rra_next(t_stack *stack, int min_val, int max_val)
{
    if (stack->size == 0)
        return 0;
    t_node *current = stack->tail;
    int min_step = -1 * stack->size;
    int step = -1;
    while (current)
    {
        if (current->value >= min_val && current->value < max_val)
            break;
        current = current->prev;
        step--;
    }
    if (min_step < step)
        min_step = step;
    return min_step;
}

int find_max_index(t_stack *stack)
{
    if (stack->size == 0)
        return 0;
    t_node *current = stack->head;
    int index = 0;
    int max_index;
    int max_val = INT_MIN;
    while (current)
    {
        if (current->value > max_val)
        {
            max_index = index;
            max_val = current->value;
        }
        current = current->next;
        index++;
    }
    return max_index;
}

int find_less_max_index(t_stack *stack, int max_index)
{
    if (stack->size == 1 || max_index < 0 || max_index >= stack->size)
        return -1;

    t_node *current = stack->head;
    int index = 0;
    int max_val = 0;
    while (current && index <= max_index)
    {
        if (index == max_index)
            max_val = current->value;
        current = current->next;
        index++;
    }

    int less_max_val = INT_MIN;
    int less_max_index = -1;
    current = stack->head;
    index = 0;
    while (current)
    {
        if (current->value < max_val && current->value > less_max_val)
        {
            less_max_val = current->value;
            less_max_index = index;
        }
        current = current->next;
        index++;
    }
    return less_max_index;
}

void slice_stack(t_stack *stack_a, t_stack *stack_b, t_operation **operations, int min_val, int max_val)
{
    int size = max_val - min_val;
    int forward_steps;
    int backward_steps;

    while (size)
    {
        forward_steps = find_ra_next(stack_a, min_val, max_val);
        backward_steps = -1 * find_rra_next(stack_a, min_val, max_val);
        if (forward_steps <= backward_steps)
            while (forward_steps--)
                do_ra(stack_a, operations);
        else
            while (backward_steps--)
                do_rra(stack_a, operations);
        do_pb(stack_a, stack_b, operations);
        if (stack_b->head->value < (min_val + max_val) / 2)
            do_rb(stack_b, operations);
        // adjust_pb(stack_b, operations);
        size--;
    }
}

int min_moves(int size, int idx)
{
    if (idx < 0 || idx >= size)
        return size; // 无效索引，返回最大
    if (idx <= size / 2)
        return idx; // 正转操作次数
    else
        return size - idx; // 反转操作次数
}

int compare_move_efficiency(int size, int max_index, int less_max_index)
{
    int moves_max = min_moves(size, max_index);
    int moves_less_max = min_moves(size, less_max_index);

    if (moves_max < moves_less_max)
        return 1;
    else if (moves_less_max < moves_max)
        return 2;
    else
        return 0;
}

void test_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    int num_chunks = get_chunk_count(stack_a->size);
    int chunk_size = stack_a->size / num_chunks;

    int max_size = stack_a->size;
    int i = 0;

    while (i < num_chunks)
    {
        if (i != num_chunks - 1)
            slice_stack(stack_a, stack_b, operations, i * chunk_size, (i + 1) * chunk_size);
        else
            slice_stack(stack_a, stack_b, operations, i * chunk_size, max_size);
        i++;
    }

    int max_index;
    int less_max_index;
    while (stack_b->size > 0)
    {
        max_index = find_max_index(stack_b);
        less_max_index = find_less_max_index(stack_b, max_index);

        // 计算移动 max_index 和 less_max_index 到栈顶所需的操作数
        int moves_max = (max_index <= stack_b->size / 2) ? max_index : stack_b->size - max_index;
        int moves_less_max = (less_max_index >= 0) ? ((less_max_index <= stack_b->size / 2) ? less_max_index : stack_b->size - less_max_index) : stack_b->size + 1; // 如果less_max_index无效，赋个较大值

        if (moves_max <= moves_less_max)
        {
            // 移动 max_index 到栈顶
            if (max_index <= stack_b->size / 2)
            {
                while (max_index--)
                    do_rb(stack_b, operations);
            }
            else
            {
                max_index = stack_b->size - max_index;
                while (max_index--)
                    do_rrb(stack_b, operations);
            }
            do_pa(stack_a, stack_b, operations);
        }
        else
        {
            // 移动 less_max_index 到栈顶
            if (less_max_index <= stack_b->size / 2)
            {
                while (less_max_index--)
                    do_rb(stack_b, operations);
            }
            else
            {
                less_max_index = stack_b->size - less_max_index;
                while (less_max_index--)
                    do_rrb(stack_b, operations);
            }
            do_pa(stack_a, stack_b, operations);
            max_index = find_max_index(stack_b);
            if (max_index <= stack_b->size / 2)
            {
                while (max_index--)
                    do_rb(stack_b, operations);
            }
            else
            {
                max_index = stack_b->size - max_index;
                while (max_index--)
                    do_rrb(stack_b, operations);
            }
            do_pa(stack_a, stack_b, operations);
            do_sa(stack_a, operations);
        }
    }
}
