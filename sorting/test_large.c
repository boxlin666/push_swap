/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:35:19 by helin             #+#    #+#             */
/*   Updated: 2025/06/05 13:25:53 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <stdlib.h>
#include <limits.h>

static int isqrt(int n)
{
    if (n <= 0) return 0;
    int left = 1;
    int right = n;
    int mid;
    int ans = 0;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        // 为了避免 mid*mid 越界，改写为 mid <= n / mid
        if (mid <= n / mid) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

static double get_alpha(int n)
{
    if (n <= 100)
        return 1.0;
    else if (n <= 500)
        return 1.3;
    else
        return 1.5;
}

void calc_initial_chunks(int N, int *out_chunk_count, int *out_chunk_size)
{
    if (N <= 0) {
        *out_chunk_count = 1;
        *out_chunk_size  = 1;
        return;
    }

    double alpha = get_alpha(N);
    int sqrt_n = isqrt(N);
    int ccount = (int)(sqrt_n * alpha);  // 截断即相当于 floor(sqrt(N) * alpha)
    if (ccount < 1) {
        ccount = 1;
    }

    // 用整数运算实现 ceil(N / ccount)：(N + ccount - 1) / ccount
    int csize = (N + ccount - 1) / ccount;

    *out_chunk_count = ccount;
    *out_chunk_size  = csize;
}

int calc_dynamic_chunk(int remaining, int pushed_so_far, int *out_chunk_count)
{
    (void)pushed_so_far; // 如果不需要可去掉这一行

    if (remaining <= 0) {
        *out_chunk_count = 1;
        return 0;
    }

    double alpha = get_alpha(remaining);
    int sqrt_r = isqrt(remaining);
    int ccount = (int)(sqrt_r * alpha);
    if (ccount < 1) {
        ccount = 1;
    }

    int csize = (remaining + ccount - 1) / ccount;
    *out_chunk_count = ccount;
    return csize;
}

int find_ra_next(t_stack *stack, int min_val, int max_val)
{
    t_node *current = stack->head;
    int step = 0;
    while (current)
    {
        if(current->value<max_val && current->value >= min_val)
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
        if(current->value<max_val && current->value >= min_val)
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
        if(current->value > max_num)
        {
            max_index = step;
            max_num = current->value;
        }
        step++;
        current = current->next;
    }
    return step;
}


void test_large(t_stack *stack_a, t_stack *stack_b, t_operation **operations)
{
    int chunk_count, chunk_size;
    while(stack_a->size > 0)
    {
        chunk_size = calc_dynamic_chunk(stack_a->size, stack_b->size, &chunk_count);
    }
}
