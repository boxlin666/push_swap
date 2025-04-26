/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:13:51 by helin             #+#    #+#             */
/*   Updated: 2025/04/26 14:13:52 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
    t_stack *a;
    t_stack *b;

    if (argc < 2)
        return (0);
    a = init_stack(argc, argv);  // 解析并建立初始栈
    b = NULL;
    if (!is_sorted(a))
        sort_stack(a, b);
    free_stack(a);
    return (0);
}
