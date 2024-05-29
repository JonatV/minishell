/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:20:46 by jveirman          #+#    #+#             */
/*   Updated: 2023/10/30 12:16:08 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*the_mem;
	size_t	len_tot;
	int		i;

	i = 0;
	len_tot = 0;
	while (s1[len_tot])
		len_tot++;
	len_tot++;
	the_mem = (char *)malloc(sizeof(char) * len_tot);
	if (the_mem == NULL)
		return (NULL);
	while (s1[i])
	{
		the_mem[i] = s1[i];
		i++;
	}
	the_mem[i] = '\0';
	return (the_mem);
}
