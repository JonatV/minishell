/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:27:43 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/07 16:26:21 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"

void	builtin_env(t_shell *shell)
{
	int		i;
	char	**array;

	array = shell->env;
	i = 0;
	while (array[i])
	{
		if (ft_strchr(array[i], '=') == 0)
		{
			i++;
			continue ;
		}
		else
			ft_putendl_fd(array[i], 1);
		i++;
	}
	ft_putstr_fd("_=", 1);
	ft_putstr_fd(shell->last_arg, 1);
	ft_putendl_fd("", 1);
}
