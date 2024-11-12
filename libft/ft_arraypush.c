/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraypush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:55:18 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 18:59:59 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_arraysize(char **array)
{
	int	array_size;

	if (!array)
		array_size = 0;
	else
		array_size = ft_arraysize(array);
	return (array_size);
}

/*
 * Add an new element at the END of the list.

 * @param	array a triple pointer to the array
 * @param	to_add the string to add
 * @return	Nothing, it changes the pointer 
 * 			from the given array to the new array.
*/
bool	ft_arraypush(char ***array, char *to_add)
{
	char	**new_array;
	int		array_size;
	int		i;

	array_size = get_arraysize(*array);
	new_array = malloc(sizeof(char *) * (array_size + 1 + 1));
	if (!new_array)
		return (false);
	i = 0;
	while (i < array_size)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[i] = ft_strdup(to_add);
	if (!new_array[i])
	{
		free(new_array);
		return (false);
	}
	new_array[++i] = NULL;
	if (*array)
		free(*array);
	*array = new_array;
	return (true);
}
