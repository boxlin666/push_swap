/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:32 by helin             #+#    #+#             */
/*   Updated: 2025/05/31 14:59:13 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../push_swap.h"
#include<stdlib.h>

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
