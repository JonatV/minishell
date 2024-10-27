/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:01:49 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/27 22:05:30 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#####################################################################
#																	#
#						ERROR MANAGEMENT							#
#																	#
#####################################################################
*/

void	fd_error(t_shell *shell, int i)
{
	if (shell->cmd_array[i].fd_in == -1)
	{
			ft_putstr(MSG_ERROR);
			ft_putstr(" : ");
			ft_putstr("in file");
			ft_putstr("\n");
			exit(0);
	}
	// panic("in file", shell);
	if (shell->cmd_array[i].fd_out == -1)
		panic("out file", shell);
}
