/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:45:17 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/12 18:26:27 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

void	builtin_echo(char **data)
{
	int	flag;
	int	i;

	if (!data[1])
	{
		write(1, "\n", 1);
		return ;
	}
	flag = 0;
	if (data[1][0] == '-' && data[1][1] == 'n' && !data[1][2])
		flag++;
	i = 1;
	if (flag)
		i++;
	while (data[i])
	{
		ft_putstr_fd(data[i], 1);
		if ((ft_arraysize(data) - 1) != i)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}
