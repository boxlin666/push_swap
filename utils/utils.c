/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:59:02 by helin             #+#    #+#             */
/*   Updated: 2025/06/27 16:43:06 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdlib.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	free_split(char **numbers)
{
	int	i;

	i = 0;
	if (!numbers)
		return ;
	while (numbers[i])
	{
		free(numbers[i]);
		i++;
	}
	free(numbers);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' || c == '\n' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}
