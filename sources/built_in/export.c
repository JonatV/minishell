/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:48:28 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 14:55:08 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_in.h"


static void	declare_env_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putstr("declare -x ");
		ft_putendl_fd(array[i], 1);
		i++;
	}
}

void	builtin_export(t_shell *shell)
{
	// if (!shell->cmd_array->data)
	// 	declare_env_array(shell->env);
	declare_env_array(shell->env); // dev
	/*
		the rest of the actual export function
		theres some edges case that i don't know how to handle
		export test
		export test=
	*/
}
