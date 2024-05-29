/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:49:38 by jveirman          #+#    #+#             */
/*   Updated: 2023/10/17 11:17:32 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	len_tot;
	void	*the_memory;
	size_t	i;

	i = 0;
	len_tot = count * size;
	the_memory = malloc(len_tot);
	if (the_memory)
	{
		while (i < len_tot)
		{
			((char *)the_memory)[i] = 0;
			i++;
		}
		return (the_memory);
	}
	return (NULL);
}
