/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:10:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 19:00:12 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 * Destroy the element at the START of the list.

 * @param	array a triple pointer to the array
 * @return	Nothing, it changes the pointer 
 * from the given array to the new array.
*/
void	ft_arrayshift(char ***array)
{
	char	**temp;

	temp = *array;
	*array = ft_arrayndup(temp + 1, ft_arraysize(temp) - 1);
	ft_arrayfree(temp);
}
