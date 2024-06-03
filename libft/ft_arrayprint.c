/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:29:17 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 11:49:51 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrayprint(char **array, char *delimiter)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putstr(array[i]);
		if (delimiter != NULL)
			ft_putstr(delimiter);
		else
			ft_putchar_fd('\n', 1);
		i++;
	}
}
