/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:53:51 by helin             #+#    #+#             */
/*   Updated: 2025/06/27 16:58:08 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (argc == 1)
		return (0);
	ctx.stack_a = init_stack();
	ctx.stack_b = init_stack();
	ctx.operations = NULL;
	ctx.operations = add_operation(ctx.operations, "head");
	if (!ctx.stack_a || !ctx.stack_b)
		error_exit(&ctx);
	if (parse_input(&ctx, argc, argv))
	{
		normalize_stack(&ctx);
		push_swap(&ctx);
		optimize_operations(ctx.operations);
		ctx.operations = compress_operations(ctx.operations,
				(t_rotation_plan){});
		print_operations(ctx.operations);
		free_operations(ctx.operations);
	}
	else
		error_exit(&ctx);
	return (0);
}
