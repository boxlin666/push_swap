/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:55:58 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 17:18:45 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"push_swap.h"
#include<unistd.h>
#include<stdlib.h>

void error_exit(t_context *ctx)
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
