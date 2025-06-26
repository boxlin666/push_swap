/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:32 by helin             #+#    #+#             */
/*   Updated: 2025/06/26 17:54:48 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	quick_sort(int *arr, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}

int	get_index(int *sorted, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (sorted[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

void	normalize_stack(t_context *ctx)
{
	int		*arr;
	int		i;
	t_node	*cur;

	i = 0;
	cur = ctx->stack_a->head;
	arr = malloc(sizeof(int) * ctx->stack_a->size);
	if (!arr)
		error_exit(ctx);
	while (cur)
	{
		arr[i++] = cur->value;
		cur = cur->next;
	}
	quick_sort(arr, 0, ctx->stack_a->size - 1);
	cur = ctx->stack_a->head;
	while (cur)
	{
		cur->value = get_index(arr, ctx->stack_a->size, cur->value);
		cur = cur->next;
	}
	free(arr);
}
