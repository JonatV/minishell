/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayfind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:07:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/06 14:44:27 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
* TODO:
*	- Check if it will still work if we make it exactly matching the word.
*		I have an issue because if I have {enter, env}, 
*		it will return pos of enter if i ask for "en"
*		This shows an inaccuracy issue.
*/
static int	str_is_in_debut(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] == to_find[i] && str[i] != '\0' && to_find[i] != '\0')
	{
		i++;
	}
	if (to_find[i] == '\0')
		return (1);
	return (0);
}

int	ft_arrayfind(char **array, char *to_find)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (str_is_in_debut(array[i], to_find))
			return (i);
		i++;
	}
	return (-1);
}
