/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/05 14:30:21 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <stdlib.h>
#include <limits.h>

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int get_chunk_count(int n)
{
    if (n <= 100)
        return 5;
    return n / 50 + 5;
}
int find_ra_next(t_stack *stack, int min_val, int max_val)
{
    t_node *current = stack->head;
    int step = 0;
    while (current)
    {
        if (current->value < max_val && current->value >= min_val)
            return step;
        step++;
        current = current->next;
    }
    return step;
}

int find_rra_next(t_stack *stack, int min_val, int max_val)
{
    t_node *current = stack->tail;
    int step = 1;
    while (current)
    {
        if (current->value < max_val && current->value >= min_val)
            return step;
        step++;
        current = current->prev;
    }
    return step;
}

int find_max_index(t_stack *stack)
{
    int max_num = -1;
    int max_index = -1;
    int step = 0;
    t_node *current = stack->head;
    while (current)
    {
        if (current->value > max_num)
        {
            max_index = step;
            max_num = current->value;
        }
        step++;
        current = current->next;
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

    int less_max_val = -1;
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
        backward_steps = find_rra_next(stack_a, min_val, max_val);
        if (forward_steps <= backward_steps)
            while (forward_steps--)
                do_ra(stack_a, operations);
        else
            while (backward_steps--)
                do_rra(stack_a, operations);
        do_pb(stack_a, stack_b, operations);
        if (stack_b->head->value < (min_val + max_val) / 2)
            do_rb(stack_b, operations);

        size--;
    }
}

static int get_moves(int idx, int stack_size)
{
    if (idx < 0 || idx >= stack_size)
        return stack_size + 1;   // 视作“无效”，返回一个很大的数，确保不会优先选中
    int up = idx;                // 用 idx 次 rb 可以把它从下标 idx 带到顶
    int down = stack_size - idx; // 用 down 次 rrb 可以把它带到顶
    return (up <= down) ? up : down;
}

/* ==== 2. 把下标为 idx 的元素旋转到栈顶 ==== */
static void rotate_to_top(t_stack *stack, int idx, t_operation **ops)
{
    if (idx < 0 || idx >= stack->size)
        return; // 无效索引，直接返回

    int up = idx;
    int down = stack->size - idx;
    if (up <= down)
    {
        /* 向上旋转 up 次：rb */
        while (up-- > 0)
        {
            do_rb(stack, ops);
        }
    }
    else
    {
        /* 向下反转 down 次：rrb */
        while (down-- > 0)
        {
            do_rrb(stack, ops);
        }
    }
}

void test_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    int chunk_count, chunk_size;
    int k = 0, N = stack_a->size;
    chunk_count = get_chunk_count(N);
    chunk_size = N / chunk_count;
    while (stack_a->size > 0)
    {
        slice_stack(stack_a, stack_b, operations, k * chunk_size, min((k + 1) * chunk_size, N));
        k++;
    }
    // print_stacks(stack_a, stack_b);
    int max_index;
    int less_max_index;

    int moves_max;
    int moves_less_max;
    while (stack_b->size > 0)
    {
        max_index = find_max_index(stack_b);
        less_max_index = find_less_max_index(stack_b, max_index);
        moves_max = get_moves(max_index, stack_b->size);
        moves_less_max = get_moves(less_max_index, stack_b->size);
        if (moves_max <= moves_less_max)
        {
            // 情况 1：先把 max_idx 旋转到顶，再 pa
            rotate_to_top(stack_b, max_index, operations);
            do_pa(stack_a, stack_b, operations);
        }
        else
        {
            // 情况 2：先把 less_max_idx 旋转到顶，再 pa
            rotate_to_top(stack_b, less_max_index, operations);
            do_pa(stack_a, stack_b, operations);

            // 重新在 B 里找一次新的 max（因为栈顶已经少了一个元素）
            max_index = find_max_index(stack_b);
            // 把新的 max 旋转到顶，再 pa
            rotate_to_top(stack_b, max_index, operations);
            do_pa(stack_a, stack_b, operations);

            // 最后做一次 sa，使刚刚 pa 回来的两项交换顺序成为正确的结果
            do_sa(stack_a, operations);
        }
    }
}
