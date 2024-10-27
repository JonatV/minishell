/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:04:30 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/27 23:07:47 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
#####################################################################
#								EXEC								#
#####################################################################
*/

void	shell_executor(t_shell *shell)
{
	here_doc_management(shell);
	update_var_lastarg(shell);
	pipes_init(shell);
	pipes_opening(shell);
	forks_process(shell);
	pipes_closing(shell);
	waiting_for_children(shell);
}

/*
* TODO:
*	- clean the exit(0) from builtin process
*		I don't understand yet how to handle the built_in command error
*/
void	execution(int i, t_shell *shell)
{
	int		built_in_index;
	char	*valid_path;

	built_in_index = is_builtin(shell->cmd_array[i].data[CMD_NAME]);
	printf("in builtin checking sent : %d\n", built_in_index);
	if (built_in_index > -1)
	{

		select_builtin(shell, i, built_in_index);
		exit(0);
	}
	else
	{
		valid_path = find_valid_path(shell->cmd_array[i].data[CMD_NAME], shell->env);
		if (0 == valid_path)
		{
			ft_putstr_fd("Error : No such command exists in the system.\n", \
			STDERR_FILENO);
			exit(127);
		}
		execve(valid_path, shell->cmd_array[i].data, shell->env);
		free(valid_path);
		panic("Execve failed", shell);
	}
}
