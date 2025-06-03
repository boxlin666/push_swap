/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:32 by helin             #+#    #+#             */
/*   Updated: 2025/06/03 15:08:43 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"
#include<stdlib.h>
#include<stdio.h>

t_stack *init_stack(void)
{
    t_stack *stack;
    stack = malloc(sizeof(t_stack));
    if (!stack)
        return (NULL);
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
    return (stack);
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}


void quick_sort(int *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}


int get_index(int *sorted, int size, int value)
{
    for (int i = 0; i < size; i++)
        if (sorted[i] == value)
            return i;
    return -1;
}

void normalize_stack(t_stack *a)
{
    int     *arr;
    int     i = 0;
    t_node  *cur = a->head;

    arr = malloc(sizeof(int) * a->size);
    if (!arr)
        error_exit();
    while (cur)
    {
        arr[i++] = cur->value;
        cur = cur->next;
    }
    quick_sort(arr, 0, a->size - 1);
    cur = a->head;
    while (cur)
    {
        cur->value = get_index(arr, a->size, cur->value);
        cur = cur->next;
    }

    free(arr);
}

void print_stacks(t_stack *stack_a, t_stack *stack_b)
{
    t_node *a = stack_a->head;
    t_node *b = stack_b->head;

    printf("\n%-10s %-10s\n", "Stack A", "Stack B");
    printf("----------------------\n");

    // 同时遍历两个栈，逐行打印
    while (a || b)
    {
        if (a)
        {
            printf("%-10d ", a->value);
            a = a->next;
        }
        else
        {
            printf("%-10s ", " ");
        }

        if (b)
        {
            printf("%-10d", b->value);
            b = b->next;
        }
        else
        {
            printf("%-10s", " ");
        }

        printf("\n");
    }

    printf("----------------------\n");
    printf("Size A: %d, Size B: %d\n\n", stack_a->size, stack_b->size);
}

void print_rotation_plan(t_rotation_plan plan)
{
    printf("=== Rotation Plan ===\n");
    printf("A index:       %d\n", plan.a_idx);
    printf("B index:       %d\n", plan.b_idx);
    printf("RA (a):        %d\n", plan.ra);
    printf("RRA (a):       %d\n", plan.rra);
    printf("RB (b):        %d\n", plan.rb);
    printf("RRB (b):       %d\n", plan.rrb);
    printf("Total moves:   %d\n", plan.total);
    printf("Strategy:      %d (%s)\n", plan.strategy,
           plan.strategy == 0 ? "rr (ra + rb)" :
           plan.strategy == 1 ? "rrr (rra + rrb)" :
           plan.strategy == 2 ? "ra + rrb" :
                                "rra + rb");
    printf("======================\n");
}


static int min_index_of_value(int *arr, int *tail_idx, int len, int value)
{
    // 在 arr[ tail_idx[0..len-1] ] 中，找到第一个 arr[ tail_idx[pos] ] >= value 的位置 pos
    // 典型二分查找
    int l = 0, r = len - 1;
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (arr[ tail_idx[mid] ] < value)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

void mark_LIS(t_stack *stack_a)
{
    if (!stack_a || stack_a->size <= 1)
    {
        // 如果栈为空或只有一个元素，直接将 in_lis 全置为 1
        t_node *tmp = stack_a->head;
        while (tmp)
        {
            tmp->in_lis = 1;
            tmp = tmp->next;
        }
        return;
    }

    int n = stack_a->size;
    // ① 申请两个辅助数组：nodes[] 存储每个节点指针，arr[] 存储节点 value
    t_node **nodes = malloc(sizeof(t_node *) * n);
    int *arr       = malloc(sizeof(int) * n);
    if (!nodes || !arr)
    {
        fprintf(stderr, "Error: malloc failed in mark_LIS\n");
        exit(EXIT_FAILURE);
    }

    // 把栈“扁平化”到数组
    t_node *cur = stack_a->head;
    for (int i = 0; i < n; i++)
    {
        nodes[i] = cur;
        arr[i]   = cur->value;
        cur       = cur->next;
    }

    // ② 准备 LIS 算法所需数组：tail_idx[], prev_idx[], 以及当前最长长度 len_LIS
    int *tail_idx = malloc(sizeof(int) * n);  // tail_idx[len] 存储“长度为 len+1 的递增子序列末尾的下标”
    int *prev_idx = malloc(sizeof(int) * n);  // prev_idx[i] = arr 中 i 位置的前驱下标
    if (!tail_idx || !prev_idx)
    {
        fprintf(stderr, "Error: malloc failed in mark_LIS\n");
        exit(EXIT_FAILURE);
    }

    int len_LIS = 1;      // 当前最长递增子序列长度
    tail_idx[0] = 0;      // 初始化，把第一个元素当作长度为1的序列末尾
    prev_idx[0] = -1;     // 第一个元素没有前驱

    // ③ 在 arr[] 上做 O(n log n) LIS
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[ tail_idx[0] ])
        {
            // arr[i] 更小：更新长度为 1 的末尾
            tail_idx[0] = i;
            prev_idx[i] = -1;
        }
        else if (arr[i] > arr[ tail_idx[len_LIS - 1] ])
        {
            // arr[i] 能接在目前最长序列后面
            prev_idx[i] = tail_idx[len_LIS - 1];
            tail_idx[len_LIS++] = i;
        }
        else
        {
            // 在 tail_idx[0..len_LIS-1] 之间二分，找第一个 >= arr[i] 的位置 pos
            int pos = min_index_of_value(arr, tail_idx, len_LIS, arr[i]);
            // 更新长度为 pos+1 的末尾
            prev_idx[i] = (pos > 0 ? tail_idx[pos - 1] : -1);
            tail_idx[pos] = i;
        }
    }

    // ④ 回溯得到一条 LIS 的下标序列（从尾向头）
    int *lis_indices = malloc(sizeof(int) * len_LIS);
    if (!lis_indices)
    {
        fprintf(stderr, "Error: malloc failed in mark_LIS\n");
        exit(EXIT_FAILURE);
    }
    int k = tail_idx[len_LIS - 1];  // LIS 最后一个元素在 arr[] 中的下标
    for (int i = len_LIS - 1; i >= 0; i--)
    {
        lis_indices[i] = k;          // 将该下标记录下来
        k = prev_idx[k];             // 跳到前驱
    }

    // ⑤ 将所有节点的 in_lis 先置为 0，然后仅把回溯得到的 lis_indices[] 对应节点置为 1
    for (int i = 0; i < n; i++)
        nodes[i]->in_lis = 0;
    for (int i = 0; i < len_LIS; i++)
    {
        int idx = lis_indices[i];
        nodes[idx]->in_lis = 1;
    }

    // ⑥ 释放临时数组
    free(nodes);
    free(arr);
    free(tail_idx);
    free(prev_idx);
    free(lis_indices);
}