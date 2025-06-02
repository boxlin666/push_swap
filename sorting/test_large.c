/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/02 14:59:32 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"
#include <stdlib.h>
#include <limits.h>

int get_chunk_count(int size)
{
    if(size<=100)
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
    if(min_step>step)
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
    if(min_step<step)
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
        index ++;
    }
    return max_index;
}

void slice_stack(t_stack *stack_a, t_stack *stack_b, t_operation **operations, int min_val, int max_val)
{
    int size = max_val - min_val;
    int forward_steps;
    int backward_steps;
    
    while(size)
    {
        forward_steps= find_ra_next(stack_a, min_val, max_val);
        backward_steps = -1 * find_rra_next(stack_a, min_val, max_val);
        if(forward_steps <= backward_steps)
            while (forward_steps --)
                do_ra(stack_a, operations);
        else
            while (backward_steps--)
                do_rra(stack_a, operations);
        do_pb(stack_a,stack_b,operations);
        if(stack_b->head->value < (min_val + max_val)/2)
            do_rrb(stack_b,operations);
        size--;
    }
}

void test_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    int num_chunks = get_chunk_count(stack_a->size);
    int chunk_size = stack_a->size / num_chunks;

    int max_size = stack_a->size;
    int i = 0;

    while(i < num_chunks)
    {
        if(i != num_chunks - 1)
            slice_stack(stack_a, stack_b, operations, i * chunk_size, (i+1)*chunk_size);
        else
            slice_stack(stack_a, stack_b, operations, i * chunk_size, max_size);
        i++;
    }

    int max_index;
    while (stack_b->size>0)
    {
        max_index = find_max_index(stack_b);
        if(max_index < stack_b->size / 2)
        {
            while (max_index--)
                do_rb(stack_b, operations);
            do_pa(stack_a,stack_b, operations);
        }
        else
        {
            max_index = stack_b->size - max_index;
            while (max_index--)
                do_rrb(stack_b, operations);
            do_pa(stack_a,stack_b, operations);
        }
    }
}
// 2 1 0 4 3