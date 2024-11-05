/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:03:35 by jveirman          #+#    #+#             */
/*   Updated: 2024/11/06 00:38:37 by jveirman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "../../includes/minishell.h"

void	forks_process(t_shell *shell, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		fd_error(shell, i);
		if (is_here_doc_available(shell, i))
			here_doc_exploit(shell, i);
		else
			fd_in_management(shell, i);
		fd_out_management(shell, i);
		pipes_closing(shell);
		execution(i, shell);
	}
	else if (pid < 0)
		panic("Fork", shell);
}

void	waiting_for_children(t_shell *shell, int built_in_triggered)
{
	int	i;
	int	status;

	i = 0;
	i = -1;
	while (++i < shell->cmd_number - built_in_triggered)
		wait(&status);
	// if (WIFEXITED(status)) // wip
	// 	shell->exit_code = WEXITSTATUS(status); //wip
}
