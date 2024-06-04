/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraypush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:55:18 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/04 10:14:32 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arraypush(char ***array, char *to_add)
{
	char	**new_array;
	int		array_size;
	int		i;

	array_size = ft_arraysize(*array);
	new_array = malloc(sizeof(char *) * (array_size + 1 + 1));
	if (!new_array)
		return ;
	i = 0;
	while ((*array)[i])
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[i] = ft_strdup(to_add);
	if (!new_array[i])
	{
		free(new_array);
		return ;
	}
	new_array[++i] = NULL;
	free(*array);
	*array = new_array;
}
