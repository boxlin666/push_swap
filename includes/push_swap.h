/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:37:44 by helin             #+#    #+#             */
/*   Updated: 2025/06/25 13:36:03 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>


typedef struct s_node
{
	int					value;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct s_stack
{
	t_node				*head;
	t_node				*tail;
	int					size;
}						t_stack;

typedef struct s_operation
{
	char				*op;
	struct s_operation	*next;
}						t_operation;

typedef struct s_context
{
	t_stack				*stack_a;
	t_stack				*stack_b;
	t_operation			*operations;
}						t_context;

typedef struct s_rotation_plan
{
	int					a_idx;
	int					b_idx;
	int					ra;
	int					rra;
	int					rb;
	int					rrb;
	int					total;
	int					strategy;
}						t_rotation_plan;

t_stack					*init_stack(void);
void					push_swap(t_stack *stack_a, t_stack *stack_b,
							t_operation **operations);
int						parse_input(t_context *ctx, int argc, char **argv);
void					quick_sort(int *arr, int low, int high);
void					normalize_stack(t_stack *a);

void					print_stacks(t_stack *stack_a, t_stack *stack_b);
void					print_rotation_plan(t_rotation_plan plan);

void					do_sa(t_stack *stack_a, t_operation **operations);
void					do_sb(t_stack *stack_b, t_operation **operations);
void					do_pa(t_stack *stack_a, t_stack *stack_b,
							t_operation **operations);
void					do_pb(t_stack *stack_a, t_stack *stack_b,
							t_operation **operations);
void					do_ra(t_stack *stack_a, t_operation **operations);
void					do_rb(t_stack *stack_b, t_operation **operations);
void					do_rra(t_stack *stack_a, t_operation **operations);
void					do_rrb(t_stack *stack_b, t_operation **operations);
void					do_ss(t_stack *stack_a, t_stack *stack_b,
							t_operation **operations);
void					do_rr(t_stack *stack_a, t_stack *stack_b,
							t_operation **operations);
void					do_rrr(t_stack *stack_a, t_stack *stack_b,
							t_operation **operations);

void					sort_small(t_stack *stack_a, t_operation **operations);
void					sort_medium(t_stack *stack_a, t_stack *stack_b,
							t_operation **operations);
void					sort_large(t_stack *stack_a, t_stack *stack_b,
							t_operation **operations);
t_operation				*add_operation(t_operation *head, const char *op);
t_operation				*optimize_operations(t_operation *head);
t_operation				*compress_operations(t_operation *head);
void					free_operations(t_operation *operations);
void					print_operations(t_operation *operations);
void					error_exit(t_context *ctx);
void					free_stack(t_stack *stack);

#endif