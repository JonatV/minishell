/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayunshift.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:05:44 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 19:00:23 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 * Add an new element at the START of the list.

 * @param	array a triple pointer to the array
 * @param	to_add the string to add
 * @return	Nothing, it changes the pointer 
 * 			from the given array to the new array.
*/
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
