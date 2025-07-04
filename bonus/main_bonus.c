/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:03:30 by helin             #+#    #+#             */
/*   Updated: 2025/07/04 11:24:54 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

static void	execute_command(t_context *ctx, char *cmd)
{
	if (ft_strncmp(cmd, "sa", 3) == 0)
		do_sa(ctx);
	else if (ft_strncmp(cmd, "sb", 3) == 0)
		do_sb(ctx);
	else if (ft_strncmp(cmd, "ss", 3) == 0)
		do_ss(ctx);
	else if (ft_strncmp(cmd, "pa", 3) == 0)
		do_pa(ctx);
	else if (ft_strncmp(cmd, "pb", 3) == 0)
		do_pb(ctx);
	else if (ft_strncmp(cmd, "ra", 3) == 0)
		do_ra(ctx);
	else if (ft_strncmp(cmd, "rb", 3) == 0)
		do_rb(ctx);
	else if (ft_strncmp(cmd, "rr", 3) == 0)
		do_rr(ctx);
	else if (ft_strncmp(cmd, "rra", 4) == 0)
		do_rra(ctx);
	else if (ft_strncmp(cmd, "rrb", 4) == 0)
		do_rrb(ctx);
	else if (ft_strncmp(cmd, "rrr", 4) == 0)
		do_rrr(ctx);
	else
		error_exit(ctx);
}

static void	read_commands(t_context *ctx)
{
	char	buffer[5];
	ssize_t	n;

	n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	while (n > 0)
	{
		buffer[n] = '\0';
		if (buffer[n - 1] == '\n')
			buffer[n - 1] = '\0';
		if (ft_strlen(buffer) > 0)
			execute_command(ctx, buffer);
		n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	}
	if (n < 0)
		error_exit(ctx);
}

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (argc == 1)
		return (0);
	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.stack_a = init_stack();
	ctx.stack_b = init_stack();
	if (!ctx.stack_a || !ctx.stack_b)
		error_exit(&ctx);
	if (parse_input(&ctx, argc, argv) < 0)
		error_exit(&ctx);
	read_commands(&ctx);
	if (is_sorted(ctx.stack_a) && ctx.stack_b->size == 0)
		write(STDOUT_FILENO, "OK\n", 3);
	else
		write(STDOUT_FILENO, "KO\n", 3);
	free_stack(ctx.stack_a);
	free_stack(ctx.stack_b);
	return (0);
}
