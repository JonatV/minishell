/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:36:49 by jveirman          #+#    #+#             */
/*   Updated: 2023/10/30 11:21:36 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	one_c;

	ptr = (unsigned char *)b;
	one_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ptr[i] = one_c;
		i++;
	}
	return (b);
}
