/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayunshift.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:05:44 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/04 10:12:08 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrayunshift(char ***array, char *to_add)
{
	char	**new_array;
	int		array_size;
	int		i;

	array_size = ft_arraysize(*array);
	new_array = malloc(sizeof(char *) * (array_size + 1 + 1));
	if (!new_array)
		return ;
	new_array[0] = ft_strdup(to_add);
	if (!new_array[0])
	{
		free(new_array);
		return ;
	}
	i = 0;
	while (i < array_size)
	{
		new_array[i + 1] = (*array)[i];
		i++;
	}
	new_array[i + 1] = NULL;
	free(*array);
	*array = new_array;
}
