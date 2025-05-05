/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helin <helin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:22:55 by helin             #+#    #+#             */
/*   Updated: 2025/04/28 13:46:49 by helin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	src_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len)
		len = 0;
	else if (start + len > src_len)
		len = src_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
