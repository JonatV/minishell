/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:31:06 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/14 21:26:58 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fd_in_management(t_shell *shell, int i)
{
	if (shell->cmd_array[i].fd_in != DEFAULT_FD)
	{
		if (dup2(shell->cmd_array[i].fd_in, STDIN_FILENO) == -1)
			panic("dup2 failed", shell);
	}
	else if (i > 0)
	{
		if (dup2(shell->pipefds[i - 1][PIPE_READ_END], STDIN_FILENO) == -1)
			panic("dup2 failed", shell);
	}
}

void	fd_out_management(t_shell *shell, int i)
{
	if (shell->cmd_array[i].fd_out != DEFAULT_FD)
	{
		if (dup2(shell->cmd_array[i].fd_out, STDOUT_FILENO) == -1)
			panic("dup2 failed", shell);
	}
	else if (i < shell->cmd_number - 1)
	{
		if (dup2(shell->pipefds[i][PIPE_WRITE_END], STDOUT_FILENO) == -1)
			panic("dup2 failed", shell);
	}
}
