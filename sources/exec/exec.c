/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:04:30 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/03 12:04:34 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/*
#####################################################################
#								EXEC								#
#####################################################################
*/

void	shell_executor(t_shell *shell, char **envp)
{
	int	num_pipes;

	num_pipes = shell->cmd_number;
	pipes_init(shell);
	pipes_opening(shell);
	forks_process(shell, envp);
	pipes_closing(shell);
	waiting_for_children(*shell);
}

void	execution(int i, t_shell *shell, char **envp)
{
	execve(shell->cmd_array[i].path, shell->cmd_array[i].data, envp);
	panic("Execve failed", shell);
}
