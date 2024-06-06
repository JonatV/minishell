/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:37:55 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/06 11:59:27 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	length_check(const char *the_string)
{
	if (the_string)
		return (ft_strlen(the_string));
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size_s1;
	size_t	size_s2;
	char	*the_mem;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	size_s1 = length_check(s1);
	size_s2 = length_check(s2);
	the_mem = (char *)malloc(sizeof(char) * (size_s1 + size_s2) + 1);
	if (the_mem == NULL)
		return (NULL);
	i = 0;
	while (i < size_s1)
	{
		the_mem[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < (size_s1 + size_s2))
		the_mem[i++] = s2[j++];
	the_mem[i] = '\0';
	return (the_mem);
}
