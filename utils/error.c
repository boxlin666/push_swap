/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:55:58 by helin             #+#    #+#             */
/*   Updated: 2025/06/27 15:31:44 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

void	error_exit(t_context *ctx)
{
	if (ctx)
	{
		free_stack(ctx->stack_a);
		free_stack(ctx->stack_b);
		free_operations(ctx->operations);
	}
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
