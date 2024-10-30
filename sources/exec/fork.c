/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:35 by jveirman          #+#    #+#             */
/*   Updated: 2024/10/30 01:22:50 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	forks_process(t_shell *shell)
{
	int			i;
	int			j;
	pid_t		pid;
	int			built_in_index;

	i = 0;
	j = 0;
	while (i < shell->cmd_number)
	{
		printf("\n\t\e[1;33m/*----------------				start fork loop [%d]				---------------*/\e[0m\n", i);

		built_in_index = is_builtin(shell->cmd_array[i].data[CMD_NAME]);
		if (built_in_index > -1 && (built_in_index == BUILTIN_EXPORT || built_in_index == BUILTIN_UNSET))
		{
			printf("\n\t\e[1;33m/*----------------				start fork loop [%d] in BUILTIN				---------------*/\e[0m\n", i);
			fd_error(shell, i);
			fd_in_management(i, j, *shell);
			fd_out_management(i, j, *shell);
			if (shell->cmd_array[i].fd_out != DEFAULT_FD)
				dup2(shell->cmd_array[i].fd_out, STDOUT_FILENO);
			else if (i != (shell->cmd_number - 1))
				dup2(shell->pipefds[j + 1], STDOUT_FILENO);
			pipes_closing(shell);
			select_builtin(shell, i, built_in_index);
			j += 2;
			i++;
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			fd_error(shell, i);
			if (is_here_doc_available(shell, i))
				here_doc_exploit(shell, i);
			else
				fd_in_management(i, j, *shell);
			fd_out_management(i, j, *shell);
			pipes_closing(shell);
			execution(i, shell);
		}
		else if (pid < 0)
			panic("Fork", shell);
		printf("\n\t\e[1;33m/*----------------				end fork loop [%d]				---------------*/\e[0m\n", i);
		j += 2;
		i++;
	}
}

void	waiting_for_children(t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < shell->cmd_number)
	{
		wait(&status);
		i++;
	}
	// if (WIFEXITED(status)) // wip
	// 	shell->exit_code = WEXITSTATUS(status); //wip
}
