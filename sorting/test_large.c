/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/05 16:59:23 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <stdlib.h>
#include <limits.h>

void td_small_sort(t_stack *stack_a, t_stack *stack_b, int n, t_operation **operations)
{
    int v1, v2, v3;
    if (n == 2)
    {
        if (stack_a->head->value > stack_a->head->next->value)
            do_sa(stack_a, operations);
    }
    else
    {
        v1 = stack_a->head->value;
        v2 = stack_a->head->next->value;
        v3 = stack_a->head->next->next->value;
        if (v1 < v3 && v2 > v3)
        {
            do_ra(stack_a, operations);
            do_sa(stack_a, operations);
            do_rra(stack_a, operations);
        }
        else if (v1 > v2 && v1 < v3)
        {
            do_sa(stack_a, operations);
        }
        else if (v1 < v2 && v1 > v3)
        {
            do_ra(stack_a, operations);
            do_ra(stack_a, operations);
            do_pb(stack_a, stack_b, operations);
            do_rra(stack_a, operations);
            do_rra(stack_a, operations);
            do_pa(stack_a, stack_b, operations);
        }
        else if (v1 > v3 && v2 < v3)
        {
            do_sa(stack_a, operations);
            do_ra(stack_a, operations);
            do_sa(stack_a, operations);
            do_rra(stack_a, operations);
        }
        else if (v1 > v2 && v2 > v3)
        {
            do_sa(stack_a, operations);
            do_ra(stack_a, operations);
            do_ra(stack_a, operations);
            do_pb(stack_a, stack_b, operations);
            do_rra(stack_a, operations);
            do_rra(stack_a, operations);
            do_pa(stack_a, stack_b, operations);
        }
    }
}

void choose_pivot(t_stack *stack, int n, int *pivot)
{
    int temp[n];
    t_node *cur = stack->head;
    for (int i = 0; i < n && cur; i++, cur = cur->next)
        temp[i] = cur->value;

    quick_sort(temp, 0, n - 1);

    *pivot = temp[n / 2];
}

void td_quicksort(t_stack *stack_a, t_stack *stack_b, int n, t_operation **operations)
{
    
    if (n <= 1)
        return;
    else if (n <= 3)
    {
        td_small_sort(stack_a, stack_b, n, operations);
        return;
    }
    int pivot;
    choose_pivot(stack_a, n, &pivot);
    int t = n;
    int x;
    int count_low = 0;
    int count_high = 0;
    while (t--)
    {
        x = stack_a->head->value;
        if (x < pivot)
        {
            do_ra(stack_a, operations);
            count_low++;
        }
        else
        {
            do_pb(stack_a, stack_b, operations);
            count_high++;
        }
    }
    t = count_high;
    while (t--)
    {
        do_pa(stack_a, stack_b, operations);
    }
    td_quicksort(stack_a, stack_b, count_high, operations);

    t = count_low;
    while (t--)
    {
        do_rra(stack_a, operations);
    }
    td_quicksort(stack_a, stack_b, count_low, operations);
}

void test_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    td_quicksort(stack_a, stack_b, stack_a->size, operations);
}

