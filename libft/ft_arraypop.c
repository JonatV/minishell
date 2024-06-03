/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraypop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:27:51 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 18:29:08 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

void	ft_arraypop(char ***array)
{
	char	**temp;

	temp = *array;
	*array = ft_arrayndup(temp, ft_arraysize(temp) - 1);
	ft_arrayfree(temp);
}
