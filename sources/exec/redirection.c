/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:31:06 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/27 10:56:57 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#####################################################################
#							FD_MANAGEMENT							#
#####################################################################
*/

void	fd_in_management(int i, int j, t_shell shell)
{
	if (shell.cmd_array[i].fd_in != DEFAULT_FD)
	{
		dup2(shell.cmd_array[i].fd_in, STDIN_FILENO);
	}
	else if (i != 0)
	{
		dup2(shell.pipefds[j - 2], STDIN_FILENO);
	}
}

void	fd_out_management(int i, int j, t_shell shell)
{
	if (shell.cmd_array[i].fd_out != DEFAULT_FD)
	{
		dup2(shell.cmd_array[i].fd_out, STDOUT_FILENO);
	}
	else if (i != (shell.cmd_number - 1))
	{
		dup2(shell.pipefds[j + 1], STDOUT_FILENO);
	}
}
