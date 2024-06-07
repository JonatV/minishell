/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayfind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:07:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/07 15:55:46 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
* INFO:
*	This version is analysing for str[i] == '=', this is
*	for the minishell env variable.
*/
static int	str_is_in_debut(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] == to_find[i] && str[i] != '\0' && to_find[i] != '\0')
		i++;
	if (to_find[i] == '\0' && (str[i] == '\0' || str[i] == '='))
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
