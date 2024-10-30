/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:31:06 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/30 20:09:18 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fd_in_management(t_shell *shell, int i)
{
	if (shell->cmd_array[i].fd_in != DEFAULT_FD)
		dup2(shell->cmd_array[i].fd_in, STDIN_FILENO);
	else if (i > 0) // if current is not the first read from previous pipe read
		dup2(shell->pipefds[i - 1][PIPE_READ_END], STDIN_FILENO);
}

void	fd_out_management(t_shell *shell, int i)
{
	int	num_cmd;

	num_cmd = shell->cmd_number;
	if (shell->cmd_array[i].fd_out != DEFAULT_FD)
		dup2(shell->cmd_array[i].fd_out, STDOUT_FILENO);
	else if (i < num_cmd - 1) // means all but the last command
		dup2(shell->pipefds[i][PIPE_WRITE_END], STDOUT_FILENO);
}
