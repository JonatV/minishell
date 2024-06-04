/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:10:12 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/04 10:13:54 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrayshift(char ***array)
{
	char	**temp;

	temp = *array;
	*array = ft_arrayndup(temp + 1, ft_arraysize(temp) - 1);
	ft_arrayfree(temp);
}
