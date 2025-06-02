/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:55:40 by helin             #+#    #+#             */
/*   Updated: 2025/05/27 14:35:35 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"
#include <stdlib.h>

int find_median(t_stack *stack)
{
    int *arr = malloc(sizeof(int) * stack->size);
    if(!arr)
        error_exit();
    t_node *current = stack->head;
    int i = 0;
    while (current)
    {
        arr[i++] = current->value;
        current = current->next;
    }
    // 简单排序
    for (int j = 0; j < stack->size - 1; j++)
        for (int k = 0; k < stack->size - j - 1; k++)
            if (arr[k] > arr[k + 1])
            {
                int temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
            }
    int median = arr[stack->size / 2];
    free(arr);
    return median;
}

int has_numbers_below_pivot(t_stack *stack, int pivot)
{
    t_node *current = stack->head;
    while (current)
    {
        if (current->value <= pivot)
            return 1;
        current = current->next;
    }
    return 0;
}

int find_max(t_stack *stack)
{
    if (stack->size == 0)
        return 0;
    t_node *current = stack->head;
    int max_val = current->value;
    while (current)
    {
        if (current->value > max_val)
            max_val = current->value;
        current = current->next;
    }
    return max_val;
}

void rotate_to_top(t_stack *stack, int value, t_operation **operations, int is_stack_a)
{
    if (stack->size == 0 || stack->head->value == value)
        return;
    t_node *current = stack->head;
    int pos = 0;
    int size = stack->size;
    while (current && current->value != value)
    {
        pos++;
        current = current->next;
    }
    int forward_steps = pos;
    int backward_steps = size - pos;
    if (forward_steps <= backward_steps)
    {
        for (int i = 0; i < forward_steps; i++)
            if (is_stack_a)
                do_ra(stack, operations);
            else
                do_rb(stack, operations);
    }
    else
    {
        for (int i = 0; i < backward_steps; i++)
            if (is_stack_a)
                do_rra(stack, operations);
            else
                do_rrb(stack, operations);
    }
}

int calculate_chunk_size(int size)
{
    if (size <= 10)
        return size / 2;
    else if (size <= 100)
        return size / 5;
    else
        return size / 10;
}

void sort_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    int pivot = find_median(stack_a);
    while (has_numbers_below_pivot(stack_a, pivot))
    {
        if (stack_a->head->value <= pivot)
            do_pb(stack_a, stack_b, operations);
        else
            do_ra(stack_a, operations);
    }
    if (stack_a->size > 5)
        sort_large(stack_a, stack_b, operations);
    else if (stack_a->size > 3)
        sort_medium(stack_a, stack_b, operations);
    else
        sort_small(stack_a, operations);
    while (stack_b->size > 0)
    {
        int max_val = find_max(stack_b);
        rotate_to_top(stack_b, max_val, operations, 0);
        do_pa(stack_a, stack_b, operations);
    }
}