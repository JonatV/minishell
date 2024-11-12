/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraypop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:27:51 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/12 18:59:46 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
/*
 * Destroy the element at the END of the list.

 * @param	array a triple pointer to the array
 * @return	Nothing, it changes the pointer 
 * from the given array to the new array.
*/
void	ft_arraypop(char ***array)
{
	char	**temp;

	temp = *array;
	*array = ft_arrayndup(temp, ft_arraysize(temp) - 1);
	ft_arrayfree(temp);
}
