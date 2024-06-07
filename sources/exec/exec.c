/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:04:30 by jveirman          #+#    #+#             */
/*   Updated: 2024/06/07 14:46:08 by jveirman         ###   ########.fr       */
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

	update_var_lastarg(shell);
	num_pipes = shell->cmd_number;
	pipes_init(shell);
	pipes_opening(shell);
	forks_process(shell, envp);
	pipes_closing(shell);
	waiting_for_children(*shell);
}

/*
* TODO:
*	- clean the exit(0) from builtin process
*/
void	execution(int i, t_shell *shell, char **envp)
{
	int	built_in_index;

	built_in_index = is_builtin(shell->cmd_array[i].data[0]);
	if (built_in_index > -1)
	{
		select_builtin(shell, i, built_in_index);
		exit(0);
	}
	else
	{
		execve(shell->cmd_array[i].path, shell->cmd_array[i].data, envp);
		panic("Execve failed", shell);
	}
}
