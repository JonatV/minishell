/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayndup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:19:44 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 11:57:57 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrayndup(char **src, int n_max)
{
	int		i;
	char	**array_dup;

	array_dup = NULL;
	i = 0;
	array_dup = malloc(sizeof(char *) * (n_max + 1));
	if (!array_dup)
		return (NULL);
	while (src[i] && i < n_max)
	{
		array_dup[i] = ft_strdup(src[i]);
		if (!array_dup)
		{
			ft_arrayfree(array_dup);
			return (NULL);
		}
		i++;
	}
	array_dup[i] = NULL;
	return (array_dup);
}
